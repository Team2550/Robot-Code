#include "subsystems/DriveSubsystem.h"

using namespace DriveConstants;

DriveSubsystem::DriveSubsystem()
	: m_frontLeft { kLeftMotorPorts[0] }
	, m_rearLeft { kLeftMotorPorts[1] }
	, m_frontRight { kRightMotorPorts[0] }
	, m_rearRight { kRightMotorPorts[1] }
	, m_leftEncoder { kLeftEncoderPorts[0], kLeftEncoderPorts[1], frc::Encoder::EncodingType::k2X }
	, m_rightEncoder { kRightEncoderPorts[0], kRightEncoderPorts[1], frc::Encoder::EncodingType::k2X }
	, m_imu {}
	, m_frontLeftLocation { kfrontLeftLocations[0], kfrontLeftLocations[1] }
	, m_frontRightLocation { kfrontRightLocations[0], kfrontRightLocations[1] }
	, m_rearLeftLocation { krearLeftLocations[0], krearLeftLocations[1] }
	, m_rearRightLocation { krearRightLocations[0], krearRightLocations[1] } {
	// Set the distance per pulse for the encoders
	m_leftEncoder.SetDistancePerPulse(4.0 / 256.0);
	m_rightEncoder.SetDistancePerPulse(4.0 / 256.0);

	// Set the default yaw axis of the accelerometer to Y
	this->SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kY);
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
	m_differentialDrive.ArcadeDrive(rotation, speed);
}

void DriveSubsystem::TankDrive(double leftSpeed, double rightSpeed) {
	// Deadzone
	if (abs(leftSpeed) < OIConstants::kDeadzone)
		leftSpeed = 0;
	if (abs(rightSpeed) < OIConstants::kDeadzone)
		rightSpeed = 0;

	m_differentialDrive.TankDrive(-leftSpeed, rightSpeed);
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

void DriveSubsystem::initializeSwerveOdometry(frc::Rotation2d imuAngle, frc::Pose2d pose) {
	delete odometry;
	odometry = new frc::SwerveDriveOdometry<4>(m_kinematics, imuAngle, pose);
}

void DriveSubsystem::SwerveDrive(units::meters_per_second_t speedV, units::meters_per_second_t speedH,
	units::radians_per_second_t rotation, units::angle::degree_t imuAngle) {
	// Deadzone
	if (abs(speedV.value()) < 0.5)
		speedV = units::meters_per_second_t { 0 };
	if (abs(speedH.value()) < 0.5)
		speedH = units::meters_per_second_t { 0 };

	speeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(speedH, speedV, rotation, frc::Rotation2d(imuAngle));
	auto [fl, fr, bl, br] = m_kinematics.ToSwerveModuleStates(speeds);

	// REST OF CODE HERE
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

/*
 * IMU functions
 */
void DriveSubsystem::ResetGyro() { m_imu.Reset(); }

void DriveSubsystem::SetYawAxis(frc::ADIS16470_IMU::IMUAxis imuAxis) { m_imu.SetYawAxis(imuAxis); }

units::angle::degree_t DriveSubsystem::GetCurrentAngle() { return m_imu.GetAngle(); }
