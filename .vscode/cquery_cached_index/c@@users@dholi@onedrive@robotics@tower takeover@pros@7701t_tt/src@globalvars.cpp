#include "main.h"

double baseW = 10.5; //10.332
double wheel = 13.18; //12.57
double wheel_two = 10;

int init_time = 0;

double abs_x, abs_y, abs_angle, abs_angle_degrees = 0;

pros::Motor front_left (14, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor front_right (12, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor back_left (16, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor back_right (13, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_ROTATIONS);

pros::Motor tilt (18, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_ROTATIONS);
pros::Motor arm (19, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_ROTATIONS);
pros::Motor intake_left (17, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS);
pros::Motor intake_right (11, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_ROTATIONS);

pros::Controller master (CONTROLLER_MASTER);

pros::Imu imu_sensor (15);

pros::ADIDigitalIn right_switch (7);
pros::ADIDigitalIn sel_switch (8);
pros::ADIDigitalIn left_switch (6);

// pros::ADIEncoder side_encoder (1, 2, 0);
