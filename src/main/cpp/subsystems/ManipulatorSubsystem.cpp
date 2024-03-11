#include "subsystems/ManipulatorSubsystem.h"

using namespace ManipulatorConstants;

ManipulatorSubsystem::ManipulatorSubsystem()
	: m_manipulator { kManiplulatorPort }
	, m_manipulatorWinch { kManipulatorWinchPort }
	, m_manipulatorLimit { kManiplulatorLimitPort } { }

/// Moves the arm. Refuses to move down if the limit switch is activated.
void ManipulatorSubsystem::MoveArm(double upValue, double downValue) {
	double modifiedValue = (upValue - downValue);
	if ((m_manipulatorLimit.Get())) {
		modifiedValue = 0;
	}
	m_manipulator.Set(modifiedValue);
}

void ManipulatorSubsystem::DriveWinch(double speed) { m_manipulatorWinch.Set(speed); }

/**
 * Pneumatic Functions
 */
void ManipulatorSubsystem::ArmGrab() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kForward); }

void ManipulatorSubsystem::ArmRelease() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kReverse); }

void ManipulatorSubsystem::ArmRest() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kOff); }