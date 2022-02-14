#include "main.h"

void armOp() {
  pros::Controller master(CONTROLLER_MASTER);
  if(master.get_digital(DIGITAL_L1) == 1) arm.move_absolute(1.85, 200);
  else if(master.get_digital(DIGITAL_L2) == 1) arm.move(-127);
  else arm.move(0);
}

void armMove(double angle, int speed) {
  arm.move_absolute(angle, speed);
}

void armWait(double angle) {
  if(arm.get_position() > angle) while(arm.get_position() > angle + 0.05) waitTrack(5);
  else while(arm.get_position() < angle - 0.05) waitTrack(5);
}
