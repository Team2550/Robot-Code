#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] }
	, m_manipulator { kManiplulatorPort }
	, m_manipulatorWinch { kManipulatorWinchPort }
	, m_manipulatorLimit { kManiplulatorLimitPort }
	, m_leftEncoder { kLeftEncoderPorts[0], kLeftEncoderPorts[1], frc::Encoder::EncodingType::k2X }
	, m_rightEncoder { kRightEncoderPorts[0], kRightEncoderPorts[1], frc::Encoder::EncodingType::k2X }
	, m_imu {} {
	// Set the distance per pulse for the encoders
	m_leftEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);
	m_rightEncoder.SetDistancePerPulse(kEncoderDistancePerPulse);

	// Set the default yaw axis of the accelerometer to Y
	this->SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kY);
}

void DriveSubsystem::ArcadeDrive(double speed, double rotation) { m_drive.ArcadeDrive(rotation, speed); }

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed) { m_drive.TankDrive(-leftSpeed, rightSpeed); }

void DriveSubsystem::ResetEncoders() {
	m_leftEncoder.Reset();
	m_rightEncoder.Reset();
}

void DriveSubsystem::ResetGyro() { m_imu.Reset(); }

frc::Encoder& DriveSubsystem::GetLeftEncoder() { return m_leftEncoder; }

frc::Encoder& DriveSubsystem::GetRightEncoder() { return m_rightEncoder; }

double DriveSubsystem::GetAverageEncoderDistance() {
	return (std::abs(m_leftEncoder.GetDistance()) + std::abs(m_rightEncoder.GetDistance())) / 2.0;
}

void DriveSubsystem::SetYawAxis(frc::ADIS16470_IMU::IMUAxis imuAxis) { m_imu.SetYawAxis(imuAxis); }

units::angle::degree_t DriveSubsystem::GetCurrentAngle() { return m_imu.GetAngle(); }

void DriveSubsystem::SetOutputScale(double scale) { m_drive.SetMaxOutput(scale); }

/// Moves the arm. Refuses to move down if the limit switch is activated.
void DriveSubsystem::MoveArm(double value) {
	double modifiedValue = value;
	if (value > 0 && !(m_manipulatorLimit.Get())) {
		modifiedValue = 0;
	}
	m_manipulator.Set(modifiedValue);
}

void DriveSubsystem::ArmGrab() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kForward); }

void DriveSubsystem::ArmRelease() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kReverse); }

void DriveSubsystem::ArmRest() { m_manipulatorSolenoid.Set(frc::DoubleSolenoid::Value::kOff); }

void DriveSubsystem::DriveWinch(double speed) { m_manipulatorWinch.Set(speed); }