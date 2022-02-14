/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
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
#include "drive.h"
#include "position.h"
#include "routes.h"
#include "mechanisms.h"
#include "display.h"
// #include "okapi/api.hpp"

extern pros::Motor front_left;
extern pros::Motor front_right;
extern pros::Motor back_left;
extern pros::Motor back_right;

extern pros::Motor tilt;
extern pros::Motor arm;
extern pros::Motor intake_left;
extern pros::Motor intake_right;

extern pros::Controller master;

extern pros::Imu imu_sensor;

extern pros::ADIDigitalIn right_switch, left_switch, sel_switch;
// extern pros::ADIEncoder side_encoder;

extern double abs_x;
extern double abs_y;
extern double abs_angle;
extern double abs_angle_degrees;

extern double wheel, wheel_two, baseW;

extern int auton_num, count, init_time;


/*
extern okapi::ChassisControllerFactory myChassis;
extern okapi::AsyncControllerFactory profileController;

auto myChassis = okapi::ChassisControllerFactory::create(
  {-1, -2}, // Left motors
  {9, 10},  // Right motors
  okapi::AbstractMotor::gearset::green, // Speed gearset
  {4_in, 10_in} // Wheel diameter, Base width
);

auto profileController = okapi::AsyncControllerFactory::motionProfile(
  1.0,  // Maximum velocity
  2.0,  // Maximum acceleration
  10.0, // Maximum jerk
  myChassis
);
*/


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

#endif  // _PROS_MAIN_H_
