#include "autons.hpp"
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/util.hpp"
#include "main.h"
#include <type_traits>


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void roller() {

  chassis.set_drive_pid(4, DRIVE_SPEED, false);
  chassis.wait_drive();
  spinRollers();
  wait(100);
  chassis.set_drive_pid(-13, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(-14, TURN_SPEED);
  chassis.wait_drive();
  shoot();
  wait(250);
  chassis.set_drive_pid(7, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  spinIntake();
  chassis.set_drive_pid(19, 127, false);
  chassis.wait_drive();
  chassis.set_drive_pid(17, 50, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  shoot();
  wait(250);
  chassis.set_turn_pid(-55, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(34.5, 50, true);
  chassis.wait_until(10);
  chassis.set_swing_pid(ez::LEFT_SWING, 0, 50);
  spinIntake();
  chassis.wait_drive();
  chassis.set_drive_pid(27, 50, true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -30, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-32, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  shoot();
  wait(250);
  auton_mode(true);
  wait(500);
  auton_mode(false);




  // spinIntake();
  // chassis.set_drive_pid(19, 127, false);
  // chassis.wait_drive();
  // chassis.set_drive_pid(19, 50, true);
  // chassis.wait_drive();
  // stopIntake();
}


void off_roller() {
  chassis.set_drive_pid(7.5, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED, false);
  chassis.wait_drive();
  spinRollers();
  wait(100);
  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(104, TURN_SPEED);
  chassis.wait_drive();
  shoot();
  wait(250);
  chassis.set_drive_pid(6.5, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();
  spinIntake();
  chassis.set_drive_pid(51, 35, true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 135, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(2, DRIVE_SPEED, true);
  chassis.wait_drive();
  shoot();
  // wait(250);
  // chassis.set_drive_pid(5, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(37, 50, true);
  // chassis.wait_drive();
  // chassis.set_swing_pid(ez::RIGHT_SWING, 121, SWING_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-33, DRIVE_SPEED, true);
  // chassis.wait_until(-15);
  // outtake();
  // chassis.wait_drive();
  // stopIntake();
  // shoot();
  stopIntake();
  wait(250);
  auton_mode(true);
  wait(500);
  auton_mode(false);
}


void awp() {
  chassis.set_drive_pid(4, DRIVE_SPEED, false);
  chassis.wait_drive();
  spinRollers();
  wait(100);
  chassis.set_drive_pid(-13, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(-14, TURN_SPEED);
  chassis.wait_drive();
  shoot();
  wait(250);
  chassis.set_drive_pid(7, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  spinIntake();
  chassis.set_drive_pid(19, 127, false);
  chassis.wait_drive();
  chassis.set_drive_pid(17, 50, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  stopIntake();
  shoot();
  wait(250);
  spinIntake();
  chassis.set_drive_pid(5, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(63, 85, true);
  chassis.wait_until(58);
  spinRollers();
  chassis.wait_drive();
  wait(500);
  chassis.set_drive_pid(-55, DRIVE_SPEED, true);
  chassis.wait_until(-8);
  spinIntake();
  chassis.wait_drive();
  stopIntake();
  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  shoot();
  wait(250);
  auton_mode(true);
  wait(500);
  auton_mode(false);
}


void skills() {
  // chassis.set_drive_pid(4, DRIVE_SPEED, false);
  // chassis.wait_drive();
  // spinRollers();
  // chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // stopIntake();
  // chassis.set_turn_pid(125, 50);
  // chassis.wait_drive();
  // spinIntake();
  // chassis.set_drive_pid(9, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // wait(1000);
  // stopIntake();
  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(6, DRIVE_SPEED, false);
  // chassis.wait_drive();
  // spinRollers();
  // chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // stopIntake();
  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-27, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // shoot();
  // chassis.set_drive_pid(21, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-135, TURN_SPEED);
  // chassis.wait_drive();
  // spinIntake();
  // chassis.set_drive_pid(33, 75, true);
  // chassis.wait_drive();
  // wait(1000);
  // stopIntake();
  // chassis.set_drive_pid(15, 75, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-20, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // shoot();
  // chassis.set_drive_pid(27, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(180, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(5, DRIVE_SPEED, false);
  // chassis.wait_drive();
  // spinRollers();
  // chassis.set_drive_pid(-2, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // stopIntake();
  // chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(9, DRIVE_SPEED, false);
  // chassis.wait_drive();
  // spinRollers();
  // chassis.set_drive_pid(-2, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // stopIntake();
  // chassis.set_drive_pid(-11, DRIVE_SPEED, true);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-135, TURN_SPEED);
  // chassis.wait_drive();
  // endgame();
  // wait(1000);
  // chassis.set_drive_pid(8, DRIVE_SPEED, true);
  // chassis.wait_drive();
}

