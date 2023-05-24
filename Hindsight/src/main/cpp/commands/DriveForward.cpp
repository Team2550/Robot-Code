#include "commands/DriveForward.h"

DriveForward::DriveForward(double speed, units::meter_t distance, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_speed(speed) {
	AddRequirements({ subsystem });

	m_distance = distance.convert<units::inches>().value();
}

void DriveForward::Initialize() {
	m_drive->ResetEncoders();
	m_drive->SetYawAxis(frc::ADIS16470_IMU::kX);
	heading = m_drive->GetCurrentAngle().value();
}

void DriveForward::Execute() { m_drive->TankDrive(m_speed, m_speed); }

void DriveForward::End(bool interrupted) { m_drive->TankDrive(0, 0); }

bool DriveForward::IsFinished() {
	double averageDistance
		= (std::abs(m_drive->GetRightEncoder().GetDistance()) + std::abs(m_drive->GetLeftEncoder().GetDistance())) / 2;

	return averageDistance >= m_distance;
}