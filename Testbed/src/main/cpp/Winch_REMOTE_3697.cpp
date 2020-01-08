#include "Winch.h"

Winch::Winch(int winchMotorPort) : winchMotor(winchMotorPort)

{
    climbMotorPort = winchMotorPort;
    winchSpeed = .8f;
}

void Winch::setSpeed(double speed)
{
    winchSpeed = speed;
}
void Winch::climb(bool climb, bool drop)
{
    if(climb)
        winchMotor.Set(winchSpeed);
    else if(drop)
        winchMotor.Set(-winchSpeed);
    else 
        winchMotor.Set(0);

}
