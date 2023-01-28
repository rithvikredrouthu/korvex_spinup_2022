#include "main.h"
#include <fstream>

void spinIntake() {
  intake.move(600);
}

void outtake() {
  intake.move(-600);
}

void spinRollers() {
  intake.move(400);
}

void stopIntake() {
  intake.move(0);
}

void wait(int sec) {
  pros::delay(sec);
}

void endgame() {
  piston1.set_value(true);
  piston2.set_value(true);
}

int cata_shoot_state = 0;
int cata_shooter_time = 0;
void shoot(){
    cata_shoot_state = 1;
    cata_shooter_time = pros::millis();

    if (cata_shoot_state == 0) {
      if (!limit_switch.get_value()) {
        cata.move(127);
      } else {              
        cata.move(0);
      }
    }

    if (cata_shoot_state == 1) {
      cata.move(127);

      if ((pros::millis() - cata_shooter_time) > 250) {
        cata_shoot_state = 0;
        cata_shooter_time = pros::millis();
      }
    }
}