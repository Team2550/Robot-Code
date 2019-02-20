#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <frc/WPILib.h>
#include <iostream>

class Manipulator
{
public:
    Manipulator(int feedHatchRetractPort, int feedHatchExtendPort, int groundHatchLowerPort, int groundHatchRaisePort, int groundHatchKickerRetractPort, int groundHatchKickerExtendPort);
    void feedHatchRetract();
    void feedHatchExtend();

    void groundHatchLower();
    void groundHatchRaise();
    
    void groundHatchKickerRetract();
    void groundHatchKickerExtend();

    bool grabGroundHatch(double pauseTime);
    
private:
    enum State { UNKOWN, RETRACT, EXTEND };

    frc::Timer grabHatchTimer;
    bool isGrabbingHatch;

    frc::DoubleSolenoid feedHatch; //2,3
    frc::DoubleSolenoid groundHatch;
    frc::DoubleSolenoid groundHatchKicker; //4,5

};
#endif