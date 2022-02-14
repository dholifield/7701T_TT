#ifndef MECHANISMS_H_
#define MECHANISMS_H_

// Intake
void intakeOp();
void intakeSpeed(int speed);
void intakeAuto(double rot, int speed);

// Arm
void armOp();
void armMove(double angle, int speed);

// Tilter
void tiltOp();
void tiltAutoOp(double kp);
void tiltAuto();
void tiltBack();

// Macros
void depositStack();
void stopCubes();

#endif
