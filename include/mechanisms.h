#ifndef MECHANISMS_H_
#define MECHANISMS_H_

// Intake
void intakeOp();
void intakeSpeed(int speed);
void intakeAuto(double rot, int speed);
void intakeWait(double rot, int speed);

// Arm
void armOp();
void armMove(double angle, int speed);
void armWait(double angle);

// Tilter
void tiltOp();
void tiltAutoOp(double kp);
void tiltAuto();
void tiltAuto(double angle);
void tiltBack();

// Macros
void deploy();
void depositStack();
void depositBigStack();
void depositStack(double angle);
void depositStackSkills();
void stopCubes();

#endif
