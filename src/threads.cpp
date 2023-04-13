#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <fstream>

using namespace std;

bool shooting = false;

void threadingCatapult(void* p) {
    int shooter_time = 0;
    int cata_state = 0;
    while(true) {
        if (cata_state == 0) {
            if (!limit_switch.get_value()) {
                cata.move_velocity(100);
            } else {              
                cata.move_velocity(0);
            }

            if (shooting) {
                shooter_time = pros::millis();
                cata_state = 1;
            }
        }

        if (cata_state == 1) {
            cata.move_velocity(100);
            shooting = false;

            if ((pros::millis() - shooter_time) > 250) {
                cata_state = 0;
                shooter_time = pros::millis();
            }
        }

        pros::delay(10);
    }

}
