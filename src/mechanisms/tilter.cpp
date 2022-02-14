#include "main.h"

bool ypressed = 0;
// Operator control for the tray tilting mechanism
void tiltOp() {
  pros::Controller master(CONTROLLER_MASTER);
  if(master.get_digital(DIGITAL_A) == 1) {
    tiltAutoOp(90); // 70
    ypressed = 0;
  }
  else if(master.get_digital(DIGITAL_B) == 1) {
    tilt.move(-100);
    ypressed = 0;
  }
  else if(master.get_digital(DIGITAL_RIGHT) == 1) {
    tiltAutoOp(45);
    ypressed = 0;
  }
  else if(!ypressed) tilt.move(0);

  if(master.get_digital(DIGITAL_Y) == 1) {
    tilt.move_absolute(0.1, 50);
    ypressed = true;
  }

  if(tilt.get_position() <= 0.1) ypressed = 0;

}


// Tilts the tray to the depositing spot using a proportion loop
void tiltAutoOp(double kp) {
  double sp = 1.9;
  double cv = tilt.get_position();
  double error = sp-cv;
  int velocity = error*kp;

  if(velocity > 200) velocity = 200;
  if(velocity < 10) velocity = 10;

  tilt.move_velocity(velocity);

  if(error <= 0.01) tilt.move_velocity(0);
}

void tiltAuto() {
  tiltAuto(1.65);
}

// Tilts the tray to a given position using a proportion loop
void tiltAuto(double angle) {
  double time = 0.01;
  double pError = 0;
  double kp = 200;
  double kd = 1;
  double sp = angle;
  bool intake = true;
  while (1) { // while (cv <= 2) {
    updatePosition();
    double cv = tilt.get_position();
    double error = sp - cv;
    double delta = (error - pError) / time;
    pError = error;
    int velocity = error*kp + delta*kd;

    if(velocity > 127) velocity = 127;
    if(velocity < 40) velocity = 40;

    tilt.move(velocity);

    if(cv > 1 && intake) {
      // intakeAuto(0.35, 75);
      // intakeSpeed(50);
      intake = false;
    }

    if((sp-cv) <= 0.01) {
      tilt.move_velocity(0);
      break;
    }
    pros::delay(1000 * time);
  }
}

void tiltBack() {
  while (tilt.get_position() > 0.06) {
    tilt.move_absolute(0.05, 50);
  }
}
