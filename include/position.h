#ifndef POSITION_H_
#define POSITION_H_

void updatePosition();
void printPosition();
void setPosition(double x, double y);
void waitTrack(int ms);

double getDistance(double x, double y);
double getAngle(double x, double y);

#endif
