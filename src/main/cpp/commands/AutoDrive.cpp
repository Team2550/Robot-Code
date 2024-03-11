#include "commands/AutoDrive.h"

AutoDrive::AutoDrive(DriveSubsystem* subsytem, double speed, int amount)
	: m_drive(subsytem)
	, m_speed(speed)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoDrive::Initialize() { }

void AutoDrive::Execute() {
	m_drive->ArcadeDrive(m_speed, 0, false);

	m_amount = m_amount - 1;
}

void AutoDrive::End(bool interrupted) { }

bool AutoDrive::IsFinished() { return m_amount <= 0; }