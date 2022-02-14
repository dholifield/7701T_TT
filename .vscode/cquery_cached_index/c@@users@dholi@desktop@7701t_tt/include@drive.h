#ifndef DRIVE_H_
#define DRIVE_H_

void move(double x, double y, double max_vel);
void move(double x, double y, double max_vel, double kp, double angle_kp);

void driveLeft(double max_vel);
void driveRight(double max_vel);

void drive(double velocity);
void drivePID(double distance, double max_vel);
void drivePID(double distance, double max_vel, double kp);

void rotate(double max_vel);
void rotatePID(double angle, double max_vel);
void rotatePID(double angle, double max_vel, double kp);

void facePos(double x, double y, double max_vel, bool front);
void facePos(double x, double y, double max_vel, bool front, double kp);

void skew(double radius, double angle);
void skew(double radius, double angle, double ki);
void skew(double radius, double angle, double kp, double kd);

void sCurve(double x, double y);

void driveOp();
void brakeMode(bool brake);

#endif
