#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] } {
	m_rearRight.SetInverted(true);
}

/*
 * Drive functions
 */
void DriveSubsystem::ArcadeDrive(double speed, double rotation, bool squareInputs) {
	speed = std::clamp(speed, -1.0, 1.0);
	rotation = std::clamp(rotation, -1.0, 1.0);
	// Deadzone
	if (abs(speed) < OIConstants::kDeadzone)
		speed = 0;
	if (abs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	if (squareInputs) {
		speed = std::copysign(speed * speed, speed);
		rotation = std::copysign(rotation * rotation, rotation);
	}

	m_frontRight.Set(frontRightFilter.Calculate(speed + rotation));
	m_rearRight.Set(rearRightFilter.Calculate(speed + rotation));
	m_frontLeft.Set(frontLeftFilter.Calculate(speed - rotation));
	m_rearLeft.Set(rearLeftFilter.Calculate(speed - rotation));
}

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed, bool squareInputs) {
	leftSpeed = std::clamp(leftSpeed, -1.0, 1.0);
	rightSpeed = std::clamp(rightSpeed, -1.0, 1.0);
	// Deadzone
	if (abs(leftSpeed) < OIConstants::kDeadzone)
		leftSpeed = 0;
	if (abs(rightSpeed) < OIConstants::kDeadzone)
		rightSpeed = 0;

	if (squareInputs) {
		leftSpeed = std::copysign(leftSpeed * leftSpeed, leftSpeed);
		rightSpeed = std::copysign(rightSpeed * rightSpeed, rightSpeed);
	}

	m_frontRight.Set(frontRightFilter.Calculate(rightSpeed));
	m_rearRight.Set(rearRightFilter.Calculate(rightSpeed));
	m_frontLeft.Set(frontLeftFilter.Calculate(leftSpeed));
	m_rearLeft.Set(rearLeftFilter.Calculate(leftSpeed));
}
