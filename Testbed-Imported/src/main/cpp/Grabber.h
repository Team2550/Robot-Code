#ifndef GRABBER_H
#define GRABBER_H

#include <frc/WPILib.h>

class Grabber
{
public:
    Grabber(int armRetractPort, int armExtendPort, int handRetractPort, int handExtendPort);
    void armGrab();
    void armRelease();

    void handGrab();
    void handRelease();

private:
    enum State { UNKOWN, RETRACT, EXTEND };
    frc::DoubleSolenoid arm; //2,3
    frc::DoubleSolenoid hand; //4,5
};
#endif