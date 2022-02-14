#include "main.h"

// operator control for the intake
void intakeOp() {
  if(master.get_digital(DIGITAL_R2) == 1) intakeSpeed(-100); // outake
  else if(master.get_digital(DIGITAL_R1) == 1) {
    if(arm.get_position() > 0.5) intakeSpeed(-200); // intake
    else intakeSpeed(200);
  }
  else intakeSpeed(0);

  if(master.get_digital(DIGITAL_X)) {
    depositBigStack();
    drivePID(-15, 63);
  }
}

// Moves the intake at a given speed. Positive intakes
void intakeSpeed(int speed) {
  intake_left.move_velocity(-speed);
  intake_right.move_velocity(speed);
}

// Moves the intake at a given speed for given rotations. Positive intakes
void intakeAuto(double rot, int speed) {
  intake_left.move_relative(-rot, speed);
  intake_right.move_relative(rot, speed);
}

void intakeWait(double rot, int speed) {
  intakeAuto(rot, speed);

  double prev_pos = intake_right.get_position();

  waitTrack(100);

  if(rot > 0) while(intake_right.get_position() < prev_pos + rot - 0.05) {
    waitTrack(5);
    if(fabs(intake_right.get_actual_velocity()) < 2 || fabs(intake_left.get_actual_velocity()) < 2) break;
  }
  else while(intake_right.get_position() > prev_pos + rot + 0.05) {
    waitTrack(5);
    if(fabs(intake_right.get_actual_velocity()) < 2 || fabs(intake_left.get_actual_velocity()) < 2) break;
  }
}






/* // stop cube function that uses the cube lock
void stopCubes() {
  int timer = 0;
  intakeAuto(-0.2, 50);
  for(int i = 0; i < 10; i++) {
    driveOp();
    pros::delay(10);
  }
  arm.move_relative(-0.3, 200);
  double armPos = arm.get_position() - 0.3;
  while(arm.get_position() >= armPos + 0.05 && timer < 50) {
    driveOp();
    pros::delay(10);
    timer++;
  }
  timer = 0;
  intakeAuto(-0.4, 100);
  double intakePos = intake_right.get_position() - 0.4;
  while(intake_right.get_position() >= intakePos + 0.05 && timer < 50) {
    driveOp();
    pros::delay(10);
    timer++;
  }
}
*/
