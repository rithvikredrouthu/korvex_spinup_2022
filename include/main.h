/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
// #include "okapi/api.hpp"
// #include "pros/api_legacy.h"
#include "EZ-Template/api.hpp"
#include "autons.hpp"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#ifndef THREADS
#define THREADS
#include "threads.h"
#endif

#ifndef BASICOP
#define BASICOP
#include "basicop.h"
#endif

// motor ports
const int chassis_lf_port = 18;
const int chassis_lm_port = 20;
const int chassis_lb_port = 9;
const int chassis_rf_port = 14;
const int chassis_rm_port = 3;
const int chassis_rb_port = 2;

const int intake_port = 4;
const int cata_port = 17;

// sensor ports
const int imu_port = 12;
const std::uint8_t limit_switch_port = 'H';

//piston ports
const std::uint8_t boost_port = 'C';
const std::uint8_t left_endgame_port = 'A';
const std::uint8_t right_endgame_port = 'B';


// motors
extern pros::Motor chassis_lf;
extern pros::Motor chassis_lm;
extern pros::Motor chassis_lb;
extern pros::Motor chassis_rf;
extern pros::Motor chassis_rm;
extern pros::Motor chassis_rb;

extern pros::Motor intake;
extern pros::Motor cata;

// endgame pistons
extern pros::ADIDigitalOut left_endgame;
extern pros::ADIDigitalOut right_endgame;

// auton pistons
extern pros::ADIDigitalOut boost;

// sensors

extern pros::Imu imu;
extern pros::ADIDigitalIn limit_switch;

extern pros::Controller master;

#endif  // _PROS_MAIN_H_
