#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] }
	, m_gyro {} { }

/*
 * Drive functions
 */
void DriveSubsystem::ArcadeDrive(double speed, double rotation, bool squareInputs) {
	speed = std::clamp(speed, -1.0, 1.0);
	rotation = std::clamp(rotation, -1.0, 1.0);
	// Deadzone
	// Uses fabs() instead of abs() to avoid casting double to int.
	if (fabs(speed) < OIConstants::kDeadzone)
		speed = 0;
	if (fabs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	if (squareInputs) {
		speed = std::copysign(speed * speed, speed);
		rotation = std::copysign(rotation * rotation, rotation);
	}

	m_frontRight.Set((rotation + speed));
	m_rearRight.Set((rotation + speed));
	m_frontLeft.Set((rotation - speed));
	m_rearLeft.Set((rotation - speed));
	m_drive.Feed();
}

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed, bool squareInputs) {
	leftSpeed = std::clamp(leftSpeed, -1.0, 1.0);
	rightSpeed = std::clamp(rightSpeed, -1.0, 1.0);
	// Deadzone
	if (fabs(leftSpeed) < OIConstants::kDeadzone)
		leftSpeed = 0;
	if (fabs(rightSpeed) < OIConstants::kDeadzone)
		rightSpeed = 0;

	if (squareInputs) {
		leftSpeed = std::copysign(leftSpeed * leftSpeed, leftSpeed);
		rightSpeed = std::copysign(rightSpeed * rightSpeed, rightSpeed);
	}

	m_frontRight.Set(rightSpeed);
	m_rearRight.Set(rightSpeed);
	m_frontLeft.Set(leftSpeed);
	m_rearLeft.Set(leftSpeed);
	m_drive.Feed();
}

void DriveSubsystem::MecanumDrive(double speedV, double speedH, double rotation, bool squareInputs) {
	// Deadzone
	if (fabs(speedV) < OIConstants::kDeadzone)
		speedV = 0;
	if (fabs(speedH) < OIConstants::kDeadzone)
		speedH = 0;
	if (fabs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	if (squareInputs) {
		speedV = std::copysign(speedV * speedV, speedV);
		speedH = std::copysign(speedH * speedH, speedH);
		rotation = std::copysign(rotation * rotation, rotation);
	}

	m_frontRight.Set(rotation + (-speedV - speedH));
	m_rearRight.Set(rotation + (-speedV + speedH));
	m_frontLeft.Set(rotation + (speedV - speedH));
	m_rearLeft.Set(rotation + (speedV + speedH));
	m_drive.Feed();
}

void DriveSubsystem::MecanumDriveField(
	double speedV, double speedH, double rotation, bool squareInputs, frc::Rotation2d gyroAngle) {
	// Deadzone
	if (fabs(speedV) < OIConstants::kDeadzone)
		speedV = 0;
	if (fabs(speedH) < OIConstants::kDeadzone)
		speedH = 0;
	if (fabs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	if (squareInputs) {
		speedV = std::copysign(speedV * speedV, speedV);
		speedH = std::copysign(speedH * speedH, speedH);
		rotation = std::copysign(rotation * rotation, rotation);
	}
	auto [frontLeft, frontRight, rearLeft, rearRight]
		= frc::MecanumDrive::DriveCartesianIK(speedH, speedV, rotation, gyroAngle);

	m_frontRight.Set(frontRight);
	m_rearRight.Set(rearRight);
	m_frontLeft.Set(frontLeft);
	m_rearLeft.Set(rearLeft);
	m_drive.Feed();
}

void DriveSubsystem::ResetAngle() { m_gyro.Reset(); }

double DriveSubsystem::GetCurrentAngle() { return m_gyro.GetAngle(); }

frc::Rotation2d DriveSubsystem::GetRotation2d() { return m_gyro.GetRotation2d(); }
