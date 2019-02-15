#ifndef GRABBER_H
#define GRABBER_H

#include <frc/WPILib.h>

class Grabber
{
private:
    bool defaultSolenoidPosition = false;
    frc::Solenoid grabberSolenoid {1};
public:
    Grabber();
    void setGrabberSolenoid(bool solenoidPosition);
};
#endif