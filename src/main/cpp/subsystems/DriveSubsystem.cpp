#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] }
	, m_leftEncoder { kLeftEncoderPorts[0], kLeftEncoderPorts[1], frc::Encoder::EncodingType::k2X }
	, m_rightEncoder { kRightEncoderPorts[0], kRightEncoderPorts[1], frc::Encoder::EncodingType::k2X } {
	// Set the distance per pulse for the encoders
	m_leftEncoder.SetDistancePerPulse(4.0 / 256.0);
	m_rightEncoder.SetDistancePerPulse(4.0 / 256.0);
}

/*
 * Drive functions
 */
void DriveSubsystem::ArcadeDrive(double speed, double rotation) {
	// Deadzone
	if (abs(speed) < OIConstants::kDeadzone)
		speed = 0;
	if (abs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	m_frontRight.Set(speed + rotation);
	m_rearRight.Set(speed + rotation);
	m_frontLeft.Set(speed - rotation);
	m_rearLeft.Set(speed - rotation);
}

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed) {
	// Deadzone
	if (abs(leftSpeed) < OIConstants::kDeadzone)
		leftSpeed = 0;
	if (abs(rightSpeed) < OIConstants::kDeadzone)
		rightSpeed = 0;

	m_frontRight.Set(rightSpeed);
	m_rearRight.Set(rightSpeed);
	m_frontLeft.Set(leftSpeed);
	m_rearLeft.Set(leftSpeed);
}

void DriveSubsystem::MecanumDrive(double speedV, double speedH, double rotation) {
	// Deadzone
	if (abs(speedV) < OIConstants::kDeadzone)
		speedV = 0;
	if (abs(speedH) < OIConstants::kDeadzone)
		speedH = 0;
	if (abs(rotation) < OIConstants::kDeadzone)
		rotation = 0;

	m_frontRight.Set(rotation + (-speedV - speedH));
	m_rearRight.Set(rotation + (-speedV + speedH));
	m_frontLeft.Set(rotation + (speedV - speedH));
	m_rearLeft.Set(rotation + (speedV + speedH));
}

void DriveSubsystem::MecanumTankDrive(double leftSpeedV, double leftSpeedH, double rightSpeedV, double rightSpeedH) {
	// Deadzone
	if (abs(leftSpeedV) < OIConstants::kDeadzone)
		leftSpeedV = 0;
	if (abs(leftSpeedH) < OIConstants::kDeadzone)
		leftSpeedH = 0;
	if (abs(rightSpeedV) < OIConstants::kDeadzone)
		rightSpeedV = 0;
	if (abs(rightSpeedH) < OIConstants::kDeadzone)
		rightSpeedH = 0;

	m_frontRight.Set(-rightSpeedV + rightSpeedH);
	m_rearRight.Set(-rightSpeedV - rightSpeedH);
	m_frontLeft.Set(leftSpeedV + leftSpeedH);
	m_rearLeft.Set(leftSpeedV - leftSpeedH);
}

/*
 * Encoder functions
 */
void DriveSubsystem::ResetEncoders() {
	m_leftEncoder.Reset();
	m_rightEncoder.Reset();
}

frc::Encoder& DriveSubsystem::GetLeftEncoder() { return m_leftEncoder; }

frc::Encoder& DriveSubsystem::GetRightEncoder() { return m_rightEncoder; }

double DriveSubsystem::GetAverageEncoderDistance() {
	return (std::abs(m_leftEncoder.GetDistance()) + std::abs(m_rightEncoder.GetDistance())) / 2.0;
}
