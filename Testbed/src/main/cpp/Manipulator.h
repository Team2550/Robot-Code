#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <frc/WPILib.h>
#include <iostream>

class Manipulator
{
public:
    Manipulator(int hatchManipulatorLowerPort, int hatchManipulatorRaisePort, int hatchKickerRetractPort, int hatchKickerExtendPort);
    void manipulatorLower();
    void manipulatorRaise();

    void hatchKickerRetract();
    void hatchKickerExtend();

    bool grabHatch(double pauseTime);
    
private:
    enum State { UNKOWN, RETRACT, EXTEND };

    frc::Timer grabHatchTimer;
    bool isGrabbingHatch;

    frc::DoubleSolenoid manipulator; //2,3
    frc::DoubleSolenoid hatchKicker; //4,5

};
#endif