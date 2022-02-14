#ifndef DRIVE_H_
#define DRIVE_H_

void move(double set_x, double set_y, double max_vel);
void move(double set_x, double set_y, double max_vel, double exit_error);
void move(double set_x, double set_y, double max_vel, double kp, double angle_kp);
void move(double set_x, double set_y, double max_vel, double kp, double angle_kp, double exit_error);
void move(double set_x, double set_y, double max_vel, double kp, double ki, double angle_kp, double exit_error);

void driveLeft(double max_vel);
void driveRight(double max_vel);

void drive(double velocity);
void drivePID(double distance, double max_vel);
void drivePID(double distance, double max_vel, double kp);

void rotate(double max_vel);
void rotatePID(double angle, double max_vel);
void rotatePID(double angle, double max_vel, double kp);
void rotatePID(double angle, double max_vel, double kp, double exit_error);

void facePos(double x, double y, double max_vel, bool front);
void facePos(double x, double y, double max_vel, bool front, double kp);

void arcPos(double x, double y, double radius, double max_vel);
void arcPos(double x, double y, double radius, double max_vel, double kp);

void arc(double angle);
void arc(double radius, double angle, double max_vel);
void arc(double radius, double angle, double max_vel, double kp, double ki, double kd);

void sCurve(double x, double y);

void driveOp();
void brakeMode(bool brake);

#endif
