#include "Winch.h"

Winch::Winch(int winchMotorPort) : winchMotor(winchMotorPort)

{
    climbMotorPort = winchMotorPort;
}

void Winch::climb(double climbSpeed)
{
    printf("climbing ,");
    printf("%f", climbSpeed);
    winchMotor.Set(climbSpeed);
}
