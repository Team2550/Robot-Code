#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft{kLeftMotorPorts[0]}
	, m_rearLeft{kLeftMotorPorts[1]}
	, m_frontRight{kRightMotorPorts[0]}
	, m_rearRight{kRightMotorPorts[1]}
	, m_leftEncoder{kLeftEncoderPorts[0], kLeftEncoderPorts[1], frc::Encoder::EncodingType::k2X}
	, m_rightEncoder{kRightEncoderPorts[0], kRightEncoderPorts[1], frc::Encoder::EncodingType::k2X} {
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

/*
 * Encoder functions
 */
void DriveSubsystem::ResetEncoders() {
	m_leftEncoder.Reset();
	m_rightEncoder.Reset();
}

frc::Encoder &DriveSubsystem::GetLeftEncoder() { return m_leftEncoder; }

frc::Encoder &DriveSubsystem::GetRightEncoder() { return m_rightEncoder; }

double DriveSubsystem::GetAverageEncoderDistance() {
	return (std::abs(m_leftEncoder.GetDistance()) + std::abs(m_rightEncoder.GetDistance())) / 2.0;
}
