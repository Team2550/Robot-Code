#include "subsystems/ManipulatorSubsystem.h"

using namespace ManipulatorConstants;

ManipulatorSubsystem::ManipulatorSubsystem()
	: m_manipulator { kManiplulatorPort }
	, m_manipulatorWinch { kManipulatorWinchPort }
	, m_manipulatorLimit { kManiplulatorLimitPort } { }

/// Moves the arm. Refuses to move down if the limit switch is activated.
void ManipulatorSubsystem::MoveArm(double upValue, double downValue) {
	if ((m_manipulatorLimit.Get())) {
		downValue = 0;
	}
	double modifiedValue = (upValue - downValue);
	m_manipulator.Set(modifiedValue);
}

void ManipulatorSubsystem::DriveWinch(double speed) { m_manipulatorWinch.Set(speed); }

/**
 * Pneumatic Functions
 */
void ManipulatorSubsystem::ArmGrab() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kForward); }

void ManipulatorSubsystem::ArmRelease() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kReverse); }

void ManipulatorSubsystem::ArmRest() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kOff); }