#include "commands/DriveTurn.h"

DriveTurn::DriveTurn(double speed, double turnheading, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_turnheading(turnheading)
	, m_speed(speed) {
	AddRequirements({ subsystem });
}

void DriveTurn::Initialize() {
	m_drive->ResetGyro();
	m_drive->SetYawAxis(frc::ADIS16470_IMU::kX);
	heading = m_drive->GetCurrentAngle().value();
	target = heading + m_turnheading;
}

void DriveTurn::Execute() {
	double error = target - m_drive->GetCurrentAngle().value();

	double kP = 0.1;

	m_drive->TankDrive((m_speed * (kP * error)), (m_speed * (-kP * error)));
}

void DriveTurn::End(bool interrupted) { m_drive->TankDrive(0, 0); }

// Figure out how to test if the turn is complete.
bool DriveTurn::IsFinished() { return std::abs(target - m_drive->GetCurrentAngle().value()) < 10; }