#include "commands/AutoPivot.h"

AutoPivot::AutoPivot(IntakeSubsystem* subsytem, bool up, int amount)
	: m_intake(subsytem)
	, m_up(up)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoPivot::Initialize() { }

void AutoPivot::Execute() {
	if (m_up)
		m_intake->PivotIntake(0.75, 0);
	else
		m_intake->PivotIntake(0, 0.75);

	m_amount = m_amount - 1;
}

void AutoPivot::End(bool interrupted) { }

bool AutoPivot::IsFinished() { return m_amount <= 0; }