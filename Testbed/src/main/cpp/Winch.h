#ifndef WINCH_H
#define WINCH_H

#include <frc/WPILib.h>
#include <math.h>
#include "Utility.h"

class Winch
{
public:
    Winch(int winchMotorPort);

    double winchSpeed;

    void setSpeed(double speed);
    void climb(bool climb, bool drop);

private:
    Victor winchMotor;
    //const double CLIMB_SPEED = 0.8;
    int climbMotorPort;
};

#endif