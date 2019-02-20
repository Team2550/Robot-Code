#include "Grabber.h"

Grabber::Grabber(int armRetractPort, int armExtendPort, int handRetractPort, int handExtendPort) :
    arm(armRetractPort, armExtendPort) , hand(handRetractPort, handExtendPort)
{
    //grabberSolenoid.Set(defaultSolenoidPosition);
    arm.Set(frc::DoubleSolenoid::kForward);
    hand.Set(frc::DoubleSolenoid::kForward);
}
//climber arms
void Grabber::armGrab()
{
    arm.Set(frc::DoubleSolenoid::kForward);
}
void Grabber::armRelease()
{
    arm.Set(frc::DoubleSolenoid::kReverse);
}
//climber hands
void Grabber::handGrab()
{
    hand.Set(frc::DoubleSolenoid::kForward);
}
void Grabber::handRelease()
{
    hand.Set(frc::DoubleSolenoid::kReverse);
}



