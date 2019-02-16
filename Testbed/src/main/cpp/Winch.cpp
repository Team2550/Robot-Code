#include "Winch.h"

Winch::Winch(int winchMotorPort) : winchMotor(winchMotorPort)

{
    climbMotorPort = winchMotorPort;
}

void Winch::climb(bool climb, bool drop)
{
    if(climb)
        winchMotor.Set(1);
    else if(drop)
        winchMotor.Set(-1);
    else 
        winchMotor.Set(0);

}
