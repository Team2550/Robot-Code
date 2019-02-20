#include "Manipulator.h"

Manipulator::Manipulator(int feedHatchRetractPort, int feedHatchExtendPort, int groundHatchLowerPort, int groundHatchRaisePort, int groundHatchKickerRetractPort, int groundHatchKickerExtendPort) :
    feedHatch(feedHatchRetractPort, feedHatchExtendPort) , groundHatch(groundHatchLowerPort, groundHatchRaisePort), groundHatchKicker(groundHatchKickerRetractPort, groundHatchKickerExtendPort)
{
    grabHatchTimer.Reset();
    grabHatchTimer.Start();

    feedHatch.Set(frc::DoubleSolenoid::kReverse);
    groundHatch.Set(frc::DoubleSolenoid::kForward);
    groundHatchKicker.Set(frc::DoubleSolenoid::kReverse);

    isGrabbingHatch = false;
}

    void Manipulator::feedHatchRetract()
    {
        feedHatch.Set(frc::DoubleSolenoid::kReverse);
    }
    void Manipulator::feedHatchExtend()
    {
        feedHatch.Set(frc::DoubleSolenoid::kForward);
    }

    void Manipulator::groundHatchLower()
    {
        groundHatch.Set(frc::DoubleSolenoid::kReverse);
    }
    void Manipulator::groundHatchRaise()
    {
        groundHatch.Set(frc::DoubleSolenoid::kForward);
    }

    void Manipulator::groundHatchKickerRetract()
    {
        groundHatchKicker.Set(frc::DoubleSolenoid::kReverse);
    }
    void Manipulator::groundHatchKickerExtend()
    {
        groundHatchKicker.Set(frc::DoubleSolenoid::kForward);
    }

    bool Manipulator::grabGroundHatch(double waitTimeSec)
    {
        if(!isGrabbingHatch)
        {
            grabHatchTimer.Reset();
            isGrabbingHatch = true;
        }
        if(grabHatchTimer.Get() < waitTimeSec)
        {
            groundHatchLower();
        }
        else if(grabHatchTimer.Get() < waitTimeSec * 2)
        {
            groundHatchRaise();
        }
        else
        {
            groundHatchRaise();
            isGrabbingHatch = false;
            return true;
        }

        return false;
        
    }
