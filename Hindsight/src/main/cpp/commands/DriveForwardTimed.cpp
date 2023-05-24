#include "commands/DriveForwardTimed.h"

DriveForwardTimed::DriveForwardTimed(double speed, units::second_t time, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_speed(speed) {
	AddRequirements({ subsystem });
	m_desiredMs = int(units::millisecond_t(time).value());
}

void DriveForwardTimed::Initialize() {
	m_drive->ResetEncoders();
	m_drive->SetYawAxis(frc::ADIS16470_IMU::kX);
	heading = m_drive->GetCurrentAngle().value();
}

void DriveForwardTimed::Execute() {
	m_drive->TankDrive(m_speed, m_speed);
	m_msOccurred += 20;
}

void DriveForwardTimed::End(bool interrupted) { m_drive->TankDrive(0, 0); }

bool DriveForwardTimed::IsFinished() { return m_msOccurred >= m_desiredMs; }