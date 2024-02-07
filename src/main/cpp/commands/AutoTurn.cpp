#include "commands/AutoTurn.h"

AutoTurn::AutoTurn(DriveSubsystem* subsytem, bool left, int amount)
	: m_drive(subsytem)
	, m_left(left)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoTurn::Initialize() { }

void AutoTurn::Execute() {
	if (m_left)
		m_drive->ArcadeDrive(0, 0.5, false);
	else
		m_drive->ArcadeDrive(0, -0.5, false);

	m_amount = m_amount - 1;
}

void AutoTurn::End(bool interrupted) { }

bool AutoTurn::IsFinished() { return m_amount <= 0; }