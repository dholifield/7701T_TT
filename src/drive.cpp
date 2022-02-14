#include "main.h"


void move(double set_x, double set_y, double max_vel)  {
  move(set_x, set_y, max_vel, 20, 10, 200, 1);
}
void move(double set_x, double set_y, double max_vel, double exit_error) {
  move(set_x, set_y, max_vel, 20, 10, 200, exit_error);
}
void move(double set_x, double set_y, double max_vel, double kp, double angle_kp) {
  move(set_x, set_y, max_vel, kp, 10, angle_kp, 1);
}
void move(double set_x, double set_y, double max_vel, double kp, double angle_kp, double exit_error) {
  move(set_x, set_y, max_vel, kp, 10, angle_kp, exit_error);
}
// Move and rotate to a desred position for autonomous control. kp around 20
void move(double set_x, double set_y, double max_vel, double kp, double ki, double angle_kp, double exit_error) {
  double time = 0.01; // time between each loop of the while loop
  double kd = 2;      // derivative constant / multiplier
  double error, deriv, integral = 0;
  double start_error = getDistance(set_x, set_y); // sets starting error to distance from position
  double prev_error = start_error;
  double vel = 0;

  double angle_ki = 250;
  double set_angle, angle_error, angle_integral, angle_deriv, angle_vel = 0;
  double start_angle_error = abs_angle - getAngle(set_x, set_y);
  double angle_prev_error = abs_angle;
  double angle_kd = 10; // derivative constant / multiplier for the angle

  bool driving = true;  // boolean to know when the robot is driving

  while(driving) {      // loops while the robot is driving
    updatePosition();   // updates the position of the robot between each loop
    int reverse = 1;    // creates a reverse int for backwards motion

    error = getDistance(set_x, set_y); // sets the error to the distance from the position
    deriv = (error - prev_error) / time; // sets the derivative to the change in error over time
    integral += error * time; // adds error times time to the integral each loop
    prev_error = error;

    set_angle = getAngle(set_x, set_y); // uses the getAngle() function to find the desired angle
    angle_error = set_angle - abs_angle; // sets the angle error to desired - current angle

    if(fabs(angle_error) > M_PI_2) { // if the desired angle is more than π/2 radians away, then it moves backwards
      angle_error = angle_error - (angle_error / fabs(angle_error)) * M_PI; // adds π radians to desired angle
      reverse = -1; // sets reverse multipler to negative
    }

    angle_deriv = (angle_error - angle_prev_error) / time; // sets angle derivative to change in error over time
    angle_integral += angle_error * time;
    angle_prev_error = angle_error;

    if(fabs(error) > fabs(start_error) * 0.8 && ki != 0) vel = integral*ki; // if robot is in first 80% of motion, only use integral for velocity
    else if(kp != 0) vel = error*kp + deriv*kd; // if robot is in last 80% of motion, add error and derivative together for velocity
    else vel = max_vel;
    vel *= reverse; // makes it negative if reversed

    if(ki == 0 && fabs(angle_error) > fabs(start_angle_error)) angle_vel = angle_integral*angle_ki;
    else angle_vel = angle_error*angle_kp + angle_deriv*angle_kd; // sets the angle velocity to the angle error + angle derivative

    if(fabs(vel) < 20) vel = 20 * vel / fabs(vel); // if set velocity is less than 20, then set it to 20
    if(fabs(vel) > max_vel) vel = max_vel * vel / fabs(vel); // if set velocity is over the supplied maximum, set it to the maximum

    driveRight(vel + angle_vel);  // moves the right side using the distance velocity + angle velocity
    driveLeft(vel - angle_vel);   // moves the left side using the distance velocity - angle velocity

    // prints information for debugging
    pros::lcd::print(1, "Error: %f", error);
    pros::lcd::print(2, "Angle Error: %f", angle_error);
    pros::lcd::print(3, "Velocity: %f", vel);
    pros::lcd::print(4, "Angle Velocity: %f", angle_vel);
    pros::lcd::print(5, "X: %f, Y: %f", abs_x, abs_y);

    if(error < exit_error) driving = false; // if the robot is within an inch of the desired position, then stop driving

    pros::delay(1000 * time); // delay by the given time interval to prevent the program from crashing
  }
  drive(0); // when the position is reached, the drive is stopped
}

// ------------------------------------------------------------------------------------------------------------------------

// Drives the left side at a set velocity
void driveLeft(double velocity) {
  front_left.move(velocity);
  back_left.move(velocity);
}
// Drives the right side at a set velocity
void driveRight(double velocity) {
  front_right.move(-velocity);
  back_right.move(-velocity);
}

// ------------------------------------------------------------------------------------------------------------------------

// Drives the robot in a stright line with a set velocity
void drive(double velocity) {
  driveLeft(velocity);
  driveRight(velocity);
}
// Drives the robot in a stright line for an indicated distance using PID.
void drivePID(double distance, double max_vel) {
  drivePID(distance, max_vel, 20);
}
// Drives the robot in a stright line for an indicated distance using PID. kp around 300
void drivePID(double distance, double max_vel, double kp) {
  double time = 0.01;
  bool driving = true;
  double ki = 10;
  double kd = 2;
  double current, error, deriv, integral = 0;
  double prev_error = distance;
  double start_left = back_left.get_position();
  double start_right = back_right.get_position();
  double vel = 0;

  int count = 0;

  while(driving) {
    updatePosition();

    current = ((back_left.get_position() - start_left) - (back_right.get_position() - start_right)) / 2;
    current *= wheel;
    error = distance - current;
    deriv = (error - prev_error) / time;
    integral += error * time;
    prev_error = error;

    if(fabs(error) > fabs(distance)*0.8) vel = integral*ki;
    else vel = error*kp + deriv*kd;

    if(fabs(vel) < 10) vel = 10 * vel / fabs(vel);
    if(fabs(vel) > max_vel) vel = max_vel * vel / fabs(vel);

    drive(vel);

    if(error <= 0.3 && error >= -0.3) count++;
    else count = 0;
    if(count == 5) driving = false;

    pros::delay(1000 * time);
  }
  drive(0);
}

// ------------------------------------------------------------------------------------------------------------------------

// Rotates the robot at a set velocity
void rotate(double velocity) {
  driveLeft(-velocity);
  driveRight(velocity);
}
// Rotates the robot to the indicated angle using PID.
void rotatePID(double angle, double max_vel) {
  rotatePID(angle, max_vel, 3);
}
void rotatePID(double angle, double max_vel, double kp) {
  rotatePID(angle, max_vel, kp, 1);
}
// Rotates the robot to the indicated angle using PID. kp around 1.25 for cubes, 2 with none
void rotatePID(double angle, double max_vel, double kp, double exit_error) {
  double time = 0.02;
  bool driving = true;
  double ki = 7;
  double kd = 0.1;
  double error, deriv, integral = 0;
  double prev_error = angle;
  double start_error = angle - abs_angle_degrees;
  double vel = 0;

  int count = 0;

  while(driving) {
    updatePosition();

    error = angle - abs_angle_degrees;
    deriv = (error - prev_error) / time;
    integral += error * time;
    prev_error = error;

    if(fabs(error) > fabs(start_error)*0.8) vel = integral*ki;
    else vel = error*kp + deriv*kd;

    if(fabs(vel) < 25) vel = 25 * vel / fabs(vel);
    if(fabs(vel) > max_vel) vel = max_vel * vel / fabs(vel);

    rotate(vel);

    // if(fabs(error) < 1) driving = false;

    if(fabs(error) < exit_error) count++;
    else count = 0;
    if(count == 2) driving = false;

    pros::delay(1000 * time);
  }
  drive(0);
}

// ------------------------------------------------------------------------------------------------------------------------

// Rotates the robot towards an indicated point using rotatePID.
void facePos(double x, double y, double max_vel, bool front) {
  facePos(x, y, max_vel, front, 3);
}
// Rotates the robot towards an indicated point using rotatePID. Allows to alternate proportion constant
void facePos(double x, double y, double max_vel, bool front, double kp) {
  double theta = getAngle(x, y); // Gets the angle it need to rotate towards

  if(!front && theta <= M_PI) theta += M_PI; // Adds half a rotation to the desired angle if you want the back of the robot to face the position
  else if(!front) theta -= M_PI;

  theta *= 180 / M_PI; // Converts theta to degress to work with the rotatePID fucntion
  rotatePID(theta, max_vel, kp);
}

// ------------------------------------------------------------------------------------------------------------------------

// Creates a skew motion until it faces the position.
void arcPos(double x, double y, double radius, double max_vel) {
  arcPos(x, y, radius, max_vel, 3);
}

// Creates a skew motion until it faces the position. Allows for alternate proportion constant
void arcPos(double x, double y, double radius, double max_vel, double kp) {
  double time = 0.02;
  bool driving = true;
  double ki = 5;
  double kd = 0.1;
  double error, deriv, integral = 0;
  double prev_error = getAngle(x, y);
  double start_error = prev_error - abs_angle_degrees;
  double vel = 0;

  int count = 0;

  while(driving) {
    updatePosition();

    double angle = getAngle(x, y);

    error = angle - abs_angle_degrees;
    deriv = (error - prev_error) / time;
    integral += error * time;
    prev_error = error;

    if(fabs(error) > fabs(start_error)*0.8) vel = integral*ki;
    else vel = error*kp + deriv*kd;

    if(fabs(vel) < 25) vel = 25 * vel / fabs(vel);
    if(fabs(vel) > max_vel) vel = max_vel * vel / fabs(vel);

    driveLeft(-vel * (radius - (angle / fabs(angle)) * baseW) / radius);
    driveRight(-vel * (radius + (angle / fabs(angle)) * baseW) / radius);

    if(fabs(error) < 1) driving = false;

    // if(error <= 0.5 && error >= -0.5) count++;
    // else count = 0;
    // if(count == 5) driving = false;

    pros::delay(1000 * time);
  }
  drive(0);
}

void arc(double angle) {
  int left_vel, right_vel = 50;
  while(abs_angle_degrees < angle) {
    if(left_vel > -4) left_vel -= 2;
    if(right_vel < 70) right_vel += 2;
    driveLeft(left_vel);
    driveRight(right_vel);
    waitTrack(5);
  }
}

// Creates an arc motion for the robot allowing it to rotate over distance. Uses PID
void arc(double radius, double angle, double max_vel) {
  arc(radius, angle, max_vel, 4, 5, 0.1);
}
// Creates an arc motion for the robot allowing it to rotate over distance. Uses PID
void arc(double radius, double angle, double max_vel, double kp, double ki, double kd) {
  double time = 0.02;
  bool driving = true;
  double set_angle = angle;
  double error, deriv, integral = 0;
  double prev_error = set_angle;
  double start_error = set_angle - abs_angle_degrees;
  double vel = 0;

  int count = 0;

  while(driving) {
    updatePosition();

    error = set_angle - abs_angle_degrees;
    deriv = (error - prev_error) / time;,
    integral += error * time;
    prev_error = error;

    if(ki != 0) {
      if(fabs(error) > fabs(start_error)*0.8) vel = integral*ki;
    } else if (kp != 0) {
      vel = error*kp + deriv*kd;
    }


    if(fabs(vel) < 15) vel = 15 * vel / fabs(vel);
    if(fabs(vel) > max_vel) vel = max_vel * vel / fabs(vel);

    driveLeft(-vel * (radius - (angle / fabs(angle)) * baseW) / radius);
    driveRight(-vel * (radius + (angle / fabs(angle)) * baseW) / radius);

    if(error <= 0.5 && error >= -0.5) count++;
    else count = 0;
    if(count == 5) driving = false;

    pros::delay(1000 * time);
  }
  drive(0);
}

// ------------------------------------------------------------------------------------------------------------------------

// Operator control for the drive
void driveOp() {
  int straight = master.get_analog(ANALOG_LEFT_Y);
  int rotate = master.get_analog(ANALOG_RIGHT_X);

  front_left.move(straight + rotate);
  back_left.move(straight + rotate);
  front_right.move(-straight + rotate);
  back_right.move(-straight + rotate);
}

// ------------------------------------------------------------------------------------------------------------------------

// Sets drive to brake mode or coast mode. True sets to brake mode and false sets to coast
void brakeMode(bool brake) {
  if (brake) {
    front_left.set_brake_mode(MOTOR_BRAKE_HOLD);
    back_left.set_brake_mode(MOTOR_BRAKE_HOLD);
    front_right.set_brake_mode(MOTOR_BRAKE_HOLD);
    back_right.set_brake_mode(MOTOR_BRAKE_HOLD);
  } else {
    front_left.set_brake_mode(MOTOR_BRAKE_COAST);
    back_left.set_brake_mode(MOTOR_BRAKE_COAST);
    front_right.set_brake_mode(MOTOR_BRAKE_COAST);
    back_right.set_brake_mode(MOTOR_BRAKE_COAST);
  }
}
