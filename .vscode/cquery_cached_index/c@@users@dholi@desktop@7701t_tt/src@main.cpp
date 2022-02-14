#include "main.h"
#include "gif-pros/gifclass.hpp"
int count = 1;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// profileController.generatePath({Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}},"drive24");
// Gif gif("/usd/tesseractres.gif", lv_scr_act());
	pros::lcd::initialize();
	imu_sensor.reset();

	// int time = pros::millis();
	// int total = 300;
	// pros::delay(300);
	// while (imu_sensor.is_calibrating()) {
	// 	pros::lcd::print(1,"IMU calibrating... %d", total);
	// 	total += 10;
	// 	pros::delay(10);
	// }
	// pros::lcd::print(1,"IMU is done calibrating");
	// pros::lcd::print(2, "(took %d ms)", total - time);

	initscr();

	pros::delay(500);
	while(imu_sensor.is_calibrating()) pros::delay(10);

	if(pros::competition::is_disabled()) {
		while(sel_switch.get_value() == 0) {
			if(right_switch.get_new_press() == 1 && count < 6) count++;
			else if(left_switch.get_new_press() == 1 && count > 1) count--;

			if(count == 1) redsmallscr();
			else if(count == 2) redbigscr();
			else if(count == 3) bluesmallscr();
			else if(count == 4) bluebigscr();
			else if(count == 5) redbig1scr();
			else if(count == 6) skillsscr();
			pros::delay(10);
		}
	}

	display();

	intake_left.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intake_right.set_brake_mode(MOTOR_BRAKE_BRAKE);
	tilt.set_brake_mode(MOTOR_BRAKE_BRAKE);
	arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
	brakeMode(1);

	switch(count) {
		case 1: smallRed(); break;
		case 2: bigRed(); break;
		case 3: smallBlue(); break;
		case 4: bigBlue(); break;
		case 5: oneCube(); break;
		case 6: skills(); break;
	}

	// depositStack();

	// smallRed();
	// autonTest();
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
	brakeMode(0);
	while (true) {
		driveOp();
		intakeOp();
		armOp();
		tiltOp();

		updatePosition();
		printPosition();

		pros::delay(10);
	}
}
