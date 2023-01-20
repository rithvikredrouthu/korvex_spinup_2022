#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"


// enum class autonStates { // the possible auton selections, change names later
// 	off,
// 	Diagonal,
// 	DiagonalMiddle,
// 	DiagonalDouble,
// 	Platform,
// 	SoloWP,
// 	Skills,
// 	test
// };

// autonStates autonSelection = autonStates::off;

// static lv_res_t DiagonalBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::Diagonal;
// 	std::cout << pros::millis() << "Diagonal" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t DiagonalMiddleBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::DiagonalMiddle;
// 	std::cout << pros::millis() << "DiagonalMiddle" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t DiagonalDoubleBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::DiagonalDouble;
// 	std::cout << pros::millis() << "DiagonalDouble" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t PlatformBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::Platform;
// 	std::cout << pros::millis() << "Platform" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t SoloWPBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::SoloWP;
// 	std::cout << pros::millis() << "SoloWP" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t SkillsBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::Skills;
// 	std::cout << pros::millis() << "Skills" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t ResetBtnAction(lv_obj_t *btn) {
// 	imu.reset();

// 	leftDrive.tarePosition();
// 	rightDrive.tarePosition();

// 	while (imu.is_calibrating() and pros::millis() < 5000)
// 	{
// 		pros::delay(10);
// 	}
// 	if (pros::millis() < 5000) std::cout << pros::millis() << ": finished calibrating!" << std::endl;
// 	return LV_RES_OK;
// }

// static lv_res_t noAutonBtnAction(lv_obj_t *btn) {
// 	autonSelection = autonStates::off;
// 	std::cout << pros::millis() << "None" << std::endl;
// 	return LV_RES_OK;
// }

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-chassis_lf_port, -chassis_lm_port, -chassis_lb_port}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{chassis_rf_port, chassis_rm_port, chassis_rb_port}

  // IMU Port
  ,11

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,36.0/60.0

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  // Print our branding over your terminal :D
  imu.reset();
	std::cout << pros::millis() << ": calibrating imu..." << std::endl;

	lv_theme_t *th = lv_theme_alien_init(360, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(th);

	std::cout << pros::millis() << ": generating paths..." << std::endl;
	//generatePaths();
	std::cout << pros::millis() << ": finished generating paths..." << std::endl;
	
	std::cout << pros::millis() << ": finished creating gui!" << std::endl;
	while (imu.is_calibrating() and pros::millis() < 5000)
	{
		pros::delay(10);
	}
	if (pros::millis() < 5000) std::cout << pros::millis() << ": finished calibrating!" << std::endl;
	else std::cout << pros::millis() << ": calibration failed, moving on" << std::endl;

	std::cout << pros::millis() << ": cata: " << cata.get_temperature() << std::endl;
	std::cout << pros::millis() << ": intake: " << intake.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisLF: " << chassis_lf.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisLM: " << chassis_lm.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisLB: " << chassis_lb.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisRF: " << chassis_rf.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisRM: " << chassis_rm.get_temperature() << std::endl;
	std::cout << pros::millis() << ": chassisRB: " << chassis_rb.get_temperature() << std::endl;
  // Initialize chassis and auton selector
  chassis.initialize();
  default_constants();
  one_mogo_constants();
  two_mogo_constants();

}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

  // This is preference to what you like to drive on.

  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


  bool intake_on = false;
  bool roller_on = false;

  int shooter_time = 0;
  int cata_state = 0;

  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .


    // intake and rollers
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake_on = !intake_on;
      intake = 127*intake_on;
    }
    
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      roller_on = !roller_on;
      intake = -127*roller_on;
    }

	  // cata
    if (cata_state == 0) {
      if (!limit_switch.get_value()) {
        cata.move(127);
      } else {              
        cata.move(0);
      }

      if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        shooter_time = pros::millis();
        cata_state = 1;
      }
    }

    if (cata_state == 1) {
      cata.move(127);

      if ((pros::millis() - shooter_time) > 250) {
        cata_state = 0;
        shooter_time = pros::millis();
      }
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
