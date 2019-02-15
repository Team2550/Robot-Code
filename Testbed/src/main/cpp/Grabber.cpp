#include "Grabber.h"

Grabber::Grabber()
{
    grabberSolenoid.Set(defaultSolenoidPosition);
}

void Grabber::setGrabberSolenoid(bool solenoidPosition)
{
    grabberSolenoid.Set(solenoidPosition);
}
