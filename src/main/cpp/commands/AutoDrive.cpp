#include "commands/AutoDrive.h"

AutoDrive::AutoDrive(DriveSubsystem* subsytem, bool forward, int amount)
	: m_drive(subsytem)
	, m_forward(forward)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoDrive::Initialize() { }

void AutoDrive::Execute() {
	if (m_forward)
		m_drive->ArcadeDrive(0.5, 0, false);
	else
		m_drive->ArcadeDrive(-0.5, 0, false);

	m_amount = m_amount - 1;
}

void AutoDrive::End(bool interrupted) { }

bool AutoDrive::IsFinished() { return m_amount <= 0; }