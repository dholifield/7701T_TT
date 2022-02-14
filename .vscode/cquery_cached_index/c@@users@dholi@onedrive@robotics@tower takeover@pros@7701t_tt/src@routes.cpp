#include "main.h"

void smallRed() {
  // 9 cube
  deploy();                             // deploys tray
  intakeSpeed(200);                     // start intakes
  move(32, 0, 63, 0, 200, 3);           // drive forward intaking first column
  move(52, -11, 63, 17, 0, 200, 1);     // drive to the right, intakeing one cube from small pyramid
  move(10, 24, 127, 15, 500, 2);        // back up toward next column of cubes
  move(33, 22, 40, 0, 100);             // move to end of second column while intaking
  rotatePID(-90, 127, 2, 5);            // rotate towards zone
  move(7, -20, 127, 7, 135, 20);        // drive to zone
  depositStack();                       // deposit the stack
  drivePID(-15, 63);                    // drive away from stack
}


void bigRed() {
  /* // 6 cube
  deploy();
  intakeSpeed(0);
  move(50, 15, 100);
  rotatePID(-100, 127, 1.1);
  intakeSpeed(100);
  move(43, -20, 127);
  rotatePID(-180, 127, 2);
  move(20, 15, 127, 2);
  facePos(20, 25, 127, 1);
  depositStack();
  drivePID(-15, 63);
  */

  // 4 cube
  deploy();
  intakeSpeed(-200);
  waitTrack(500);
  intakeSpeed(200);
  waitTrack(750);
  drivePID(17, 63);
  rotatePID(-90, 127, 1.5);
  move(16, -32, 50);
  drive(50);
  waitTrack(500);
  move(30, -5, 127);
  facePos(0, 10, 127, true, 3);
  drivePID(getDistance(0, 10) - 22, 100);
  depositStack();
  drivePID(-15, 63);
  rotatePID(-65, 63);


  /* // 4 cube
  deploy();
  intakeSpeed(200);
  move(50, -2, 63);
  move(10, 0, 127);
  move(17, -20, 63);
  drive(50);
  waitTrack(500);
  move(40, 5, 127);
  facePos(10, 25, 127, true);
  drivePID(getDistance(10, 25) - 20, 80);
  depositStack();
  drivePID(-20, 63);
  */
}


void smallBlue() {
  /* // 8 cube
  deploy();
  intakeSpeed(200);                        // start intakes
  move(36, 0, 63);                         // drive forward intaking first column
  move(50.5, 10, 63);                         // drive to the left, intakeing one cube from small pyramid
  move(10, -24, 127, 15, 500, 3);             // back up toward next column of cubes
  move(28, -22, 50);                       // move to end of second column while intaking
  facePos(6, 20, 127, true, 1.5);          // rotate towards zone
  intakeSpeed(75);                         // slow down intakes
  drivePID(getDistance(6, 20) - 16, 127);  // drive to unprotected zone, subtracting robot length
  depositStack();                          // deposit the stack
  drivePID(-15, 63);
  */


  deploy();                             // deploys tray
  intakeSpeed(200);                     // start intakes
  move(30, 0, 63, 0, 200, 3);           // drive forward intaking first column
  move(52, 10.5, 63, 0, 0, 150, 1);      // drive to the right, intakeing one cube from small pyramid
  move(54, 13, 63, 15, 0, 150, 1);
  move(10, -24, 127, 20, 500, 2);       // back up toward next column of cubes
  move(30, -22, 50, 0, 100);            // move to end of second column while intaking
  arc(90);                             // arc towards zone
  move(7, 22, 127, 7, 0, 135, 19);      // drive towards zone
  depositBigStack();                    // deposit the stack
  drivePID(-15, 63);                    // drive away from stack


  /* // 10 cube
  intakeSpeed(-200); // deploy
  waitTrack(1200); // wait for deploy
  intakeSpeed(200); // intake cubes
  move(36, 0, 63);
  move(51, 10, 63);
  rotatePID(-70, 127);
  move(abs_x, -8, 63, 17, 150);
  move(20, -23, 50, 17, 100);
  intakeAuto(5, 200); // fully intake cubes
  facePos(5, 20, 127, true, 1.5); // rotate towards zone
  drivePID(getDistance(8, 20) - 18, 127); // drive towards the zone
  depositStack(); // deposit the stack
  tiltBack(); // puts the tray down
  */
}


void bigBlue() {

}


void oneCube() {
  deploy(); // deploy
}


void skills() {
  // First Column
  deploy();
  intakeSpeed(200); // intake cubes
  move(36, 0, 63); // get first column of cubes
  move(51, 10, 63);
  waitTrack(500);
  // First Tower
  drivePID(-10, 127, 25);
  stopCubes();
  armWait(0.5);
  facePos(27, 28, 127, true);
  drivePID(5, 100, 25);
  intakeAuto(-2, 75);
  waitTrack(500);
  /* // Second Tower
  intakeSpeed(200);
  drivePID(-7, 127);
  armMove(-0.05, 200);
  armWait(0.5);
  facePos(60, -10, 127, 1, 2);
  stopCubes();
  armWait(1);
  drivePID(5, 127);
  intakeAuto(-2, 100);
  waitTrack(500);
  */
  // Continue Column
  drivePID(-7, 127, 25);
  armMove(-0.05, 200);
  intakeSpeed(200);
  rotatePID(0, 127);
  move(100, 0, 50);
  /* // Third Tower
  stopCubes();
  waitTrack(250);
  facePos(107, 28, 127, 1, 2);
  drivePID(5, 127);
  intakeAuto(-2, 100);
  waitTrack(500);
  drivePID(-10, 127);
  armMove(-0.05, 200);
  intakeSpeed(200);
  */
  // Deposit 7 Cubes
  facePos(119, 10, 127, true);
  drivePID(getDistance(119, 10) - 5, 100);
  waitTrack(250);
  depositStackSkills();
  // Second Tower
  drivePID(-10, 63);
  rotatePID(-90, 127, 1.5);
  intakeSpeed(200);
  move(115, -30, 63, 10, 200);
  drive(63);
  waitTrack(250);
  drivePID(-10, 100);
  intakeWait(-1, 100);
  armMove(1.8, 200);
  armWait(1.7);
  drivePID(5, 100);
  intakeAuto(-2, 100);
  waitTrack(750);
  // Next Column
  rotatePID(-180, 127, 2);
  drivePID(-10, 100);
  intakeSpeed(200);
  armMove(-0.05, 200);
  armWait(0);
  move(15, -24, 63);
  waitTrack(500);
  drivePID(-15, 127);
  // Fifth Tower
  armMove(1.8, 200);
  intakeAuto(-0.75, 200);
  armWait(1.5);
  facePos(12, -45, 127, true);
  drivePID(5, 127);
  intakeAuto(-2, 100);
  waitTrack(500);
  drivePID(-10, 127);
  armMove(-0.05, 200);
  intakeSpeed(200);
  // deposit second stack
  facePos(10, 10, 127, 1);
  drivePID(getDistance(10, 10) - 5, 100);
  depositStackSkills();
  drivePID(-25, 63);
  // third tower
  rotatePID(-360, 127);
  intakeSpeed(200);
  drivePID(30, 63);
  drivePID(-10, 127);
  intakeWait(-1, 100);
  armMove(1.4, 200);
  armWait(1.3);
  drivePID(5, 100);
  intakeAuto(-2, 100);
  waitTrack(500);
  armMove(-0.05, 200);

}


void autonTest() {
  deploy();
}
