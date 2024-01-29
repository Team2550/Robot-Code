#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] } { }

/*
 * Drive functions
 */
void DriveSubsystem::ArcadeDrive(double speed, double rotation) {
	// Deadzone
	if (abs(speed) < OIConstants::kDeadzone)
		speed = 0;
	if (abs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	// We really shouldn't be inverting this here
	// I would prefer to do it on hardware for the sake of cleanliness.
	// but I digress.
	m_frontRight.Set(frontRightFilter.Calculate(speed + rotation));
	m_rearRight.Set(rearRightFilter.Calculate(-(speed + rotation)));
	m_frontLeft.Set(frontLeftFilter.Calculate(-(speed - rotation)));
	m_rearLeft.Set(rearLeftFilter.Calculate(-(speed - rotation)));
}

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed) {
	// Deadzone
	if (abs(leftSpeed) < OIConstants::kDeadzone)
		leftSpeed = 0;
	if (abs(rightSpeed) < OIConstants::kDeadzone)
		rightSpeed = 0;

	m_frontRight.Set(frontRightFilter.Calculate(rightSpeed));
	m_rearRight.Set(rearRightFilter.Calculate(-rightSpeed));
	m_frontLeft.Set(frontLeftFilter.Calculate(-leftSpeed));
	m_rearLeft.Set(rearLeftFilter.Calculate(-leftSpeed));
}
