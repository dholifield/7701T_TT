#include "main.h"

// variables for position tracking
double prev_left, prev_right, prev_angle, center_radius, center_displ = 0;
double prev_side, side_radius, side_displ = 0;

// ------------------------------------------------------------------------------------------------------------------------

// returns the distance from the robots position to the given position
double getDistance(double x, double y) {
  x -= abs_x;
  y -= abs_y;
  return sqrt(x*x + y*y);
}
// returns the angle from the robot to the given position
double getAngle(double x, double y) {
  x -= abs_x;
  y -= abs_y;
  double theta = atan2(y,x);

  double delta_angle = theta - abs_angle;
  while(fabs(delta_angle) > M_PI) {
    theta -= (delta_angle / fabs(delta_angle)) * 2 * M_PI;
    delta_angle = theta - abs_angle;
  }

  return theta;
}

// ------------------------------------------------------------------------------------------------------------------------

// sets the starting position of the robot
void setPosition(double x, double y) {
  abs_x = x;
  abs_y = y;
}
// tracks the position and rotation of the robot using odometry. Uses drive motors
void updatePosition() {
  double left_displ = (back_left.get_position() - prev_left) * wheel;
  double right_displ = -(back_right.get_position() - prev_right) * wheel;
  prev_left = back_left.get_position();
  prev_right = back_right.get_position();
  double center_arc = (left_displ + right_displ) / 2;

  abs_angle_degrees = -imu_sensor.get_rotation();
  abs_angle = abs_angle_degrees * M_PI / 180;
  double delta_angle = abs_angle - prev_angle;
  prev_angle = abs_angle;

  if(delta_angle != 0) {
    center_radius = center_arc / delta_angle;
    center_displ = 2 * sin(delta_angle / 2) * center_radius;
  }
  else {
    center_displ = center_arc;
  }

  abs_x += center_displ * cos(abs_angle);
  abs_y += center_displ * sin(abs_angle);
}


// Prints the x and y posistion of the robot as well as the angle
void printPosition() {
  pros::lcd::print(1, "x: %f", abs_x);
  pros::lcd::print(2, "y: %f", abs_y);
  pros::lcd::print(3, "angle: %f", abs_angle_degrees);

//   pros::lcd::print(5, "encoder: %d", side_encoder.get_value());
}

// waits for a specified time while updating the position of the robot
void waitTrack(int ms) {
  ms /= 5;
  for(int i = 0; i < ms; i++) {
    pros::delay(5);
    updatePosition();
  }
}
