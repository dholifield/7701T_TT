#include "main.h"

void smallRed() {
  intakeSpeed(-200); // delpoy
  waitTrack(1500);
  intakeSpeed(200); // intake cubes
  drivePID(34, 63); // drive forward while intaking cubes
  intakeAuto(3, 200); // intake cubes fully
  facePos(10, 24, 127, false); // rotate towards next column of cubes
  drivePID(-getDistance(10, 25), 127); // drive back toward the column of cubes
  rotatePID(0, 127); // rotate towards the column of cubes
  // facePos(23, -25, 127, 1, 3); // rotate towards the column of cubes
  intakeSpeed(200); // intake cubes
  drivePID(getDistance(24, 25), 63); // drive forward while intaking cubes
  intakeAuto(5, 200); // fully intake cubes
  facePos(6, -20, 127, true, 1.5); // rotate towards zone
  drivePID(getDistance(6, -20) - 14, 127); // drive towards the zone
  depositStack(); // deposit the stack
  tiltBack(); // puts the tray down
}


void bigRed() {

}


void smallBlue() {

  // 7 cube
  intakeSpeed(-200); // deploy
  waitTrack(1200); // wait for deploy
  intakeSpeed(200); // intake cubes
  drivePID(34, 63); // drive forward while intaking cubes
  intakeAuto(3, 200); // intake cubes fully
  facePos(10, -24, 127, false); // rotate towards next column of cubes
  drivePID(-getDistance(10, -24), 127); // drive back toward the column of cubes
  rotatePID(0, 127); // rotate towards the column of cubes
  // facePos(23, -25, 127, 1, 3); // rotate towards the column of cubes
  intakeSpeed(200); // intake cubes
  drivePID(getDistance(24, -24), 63); // drive forward while intaking cubes
  intakeAuto(5, 200); // fully intake cubes
  facePos(0, 20, 127, true, 1.5); // rotate towards zone
  drivePID(getDistance(0, 20) - 17, 127); // drive towards the zone
  depositStack(); // deposit the stack
  tiltBack(); // puts the tray down

  /*
  // 9 cube
  intakeSpeed(-200); // deploy
  waitTrack(1200); // wait for deploy
  intakeSpeed(200); // intake cubes
  drivePID(34, 63); // drive forward while intaking cubes
  skew(13, -180, 40); // skew 180 degrees
  drivePID(15, 63);
  intakeAuto(3, 200);
  rotatePID(-250, 127, 2);
  // facePos(2, 20, 127, true, 1.5); // rotate towards zone
  drivePID(30, 127); // drive towards the zone
  depositStack(); // deposit the stack
  tiltBack(); // puts the tray down
  */
}


void bigBlue() {

}


void oneCube() {
  intakeAuto(-10, 200);
}


void skills() {

}


void autonTest() {
  rotatePID(45, 127);
}
