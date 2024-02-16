#include "subsystems/ClimbSubsystem.h"

using namespace ClimbConstants;

ClimbSubsystem::ClimbSubsystem()
	: m_climbMotor { kClimbMotor }
    , m_climbSwitch { kClimbSwitch } { }

void ClimbSubsystem::Climb() { m_climbMotor.Set(-1); }

void ClimbSubsystem::Reach() { m_climbMotor.Set(0.5); }

void ClimbSubsystem::Stop() { m_climbMotor.Set(0); }