#include "main.h"

// deposits a stack
void depositStack() {
  depositStack(1.75);
}

void depositStack(double angle) {
  drive(30);
  intakeAuto(1, 200);
  waitTrack(150);
  intakeAuto(-0.65, 50);
  waitTrack(200);
  tiltAuto(angle); // tilt to drop cubes
  intakeWait(1, 200);
  intakeAuto(-2, 100); // outtake/drop
  tilt.move_absolute(0, 75);
}

void depositBigStack() {
  drive(30);
  intakeAuto(1, 200);
  waitTrack(150);
  intakeAuto(-0.35, 50);
  waitTrack(200);
  tiltAuto(1.75); // tilt to drop cubes
  // intakeWait(0.25, 200);
  intakeAuto(-2, 100); // outtake/drop
  tilt.move_absolute(0, 75);
}

void depositStackSkills() {
  drive(30);
  intakeAuto(1, 200);
  waitTrack(150);
  intakeAuto(-0.65, 50);
  waitTrack(250);
  tiltAuto(1.7); // tilt to drop cubes
  intakeWait(2, 200);
  intakeAuto(-2, 100); // outtake/drop
  tilt.move_absolute(0, 100);
}

// stops the cubes using the cube lock
void stopCubes() {
  armMove(1.4, 200);
  intakeAuto(-0.75, 100);
}

// deploys the robot at the start of a match
void deploy() {
  intakeSpeed(-200);
  waitTrack(1250);
  // waitTrack(250);
  // armMove(0.6, 200);
  // armWait(0.6);
  // armMove(0, 200);
  // armWait(0);

  // remove after testing
  // intakeSpeed(0);
  // pros::lcd::print(6, "time: %d", (int)pros::millis()); // print out the time to complete auton
}
