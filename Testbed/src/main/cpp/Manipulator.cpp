#include "Manipulator.h"

Manipulator::Manipulator(int manipulatorLowerPort, int manipulatorRaisePort, int hatchKickerRetractPort, int hatchKickerExtendPort) :
    manipulator(manipulatorLowerPort, manipulatorRaisePort) , hatchKicker(hatchKickerRetractPort, hatchKickerExtendPort)
{
    grabHatchTimer.Reset();
    grabHatchTimer.Start();

    manipulator.Set(frc::DoubleSolenoid::kForward);
    hatchKicker.Set(frc::DoubleSolenoid::kReverse);

    isGrabbingHatch = false;
}

    void Manipulator::manipulatorLower()
    {
        manipulator.Set(frc::DoubleSolenoid::kReverse);
    }
    void Manipulator::manipulatorRaise()
    {
        manipulator.Set(frc::DoubleSolenoid::kForward);
    }

    void Manipulator::hatchKickerRetract()
    {
        hatchKicker.Set(frc::DoubleSolenoid::kReverse);
    }
    void Manipulator::hatchKickerExtend()
    {
        hatchKicker.Set(frc::DoubleSolenoid::kForward);
    }
    bool Manipulator::grabHatch(double waitTimeSec)
    {
        if(!isGrabbingHatch)
        {
            grabHatchTimer.Reset();
            isGrabbingHatch = true;
        }
        if(grabHatchTimer.Get() < waitTimeSec)
        {
            manipulatorLower();
        }
        else if(grabHatchTimer.Get() < waitTimeSec * 2)
        {
            manipulatorRaise();
        }
        else
        {
            manipulatorRaise();
            isGrabbingHatch = false;
            return true;
        }

        return false;
        
    }
