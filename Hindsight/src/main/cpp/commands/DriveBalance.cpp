#include "commands/DriveBalance.h"

DriveBalance::DriveBalance(double speed, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_speed(speed) {
	AddRequirements({ subsystem });
}

void DriveBalance::Initialize() { m_status = 0; }

void DriveBalance::Execute() {
	while (std::abs(m_drive->GetCurrentAngle().value()) < 30.0 && m_status == 0) {
		m_drive->SetYawAxis(frc::ADIS16470_IMU::kX);
		m_drive->TankDrive(m_speed, m_speed);
	}
	if (std::abs(m_drive->GetCurrentAngle().value()) >= 30.0 && m_status == 0) {
		m_status = 1;
	}

	m_drive->SetYawAxis(frc::ADIS16470_IMU::kZ);

	currentAngle = m_drive->GetCurrentAngle().value();

	error = 0 - currentAngle;

	while (abs(error) > 5 && m_status == 1) {
		currentAngle = m_drive->GetCurrentAngle().value();

		error = 0 - currentAngle;

		double speedcalc = (0.005 * error);

		m_drive->TankDrive(speedcalc, speedcalc);
	}
	if (abs(error) <= 5 && m_status == 1) {
		m_status = 2;
	}
}

bool DriveBalance::IsFinished() { return m_status == 2; }