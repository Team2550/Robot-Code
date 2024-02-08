#include "commands/AutoTurn.h"

AutoTurn::AutoTurn(DriveSubsystem* subsytem, bool left, int amount, frc::DriverStation* ds)
	: m_drive(subsytem)
	, m_left(left)
	, m_amount(amount)
	, m_ds(ds) {
	AddRequirements({ subsytem });
}

void AutoTurn::Initialize() {
	// Commands for this were written from the blue perspective,
	// So all 'Red alliance' autos will need turns inverted.
	if (m_ds->GetAlliance() == m_ds->kRed) {
		m_left = !m_left;
	}
}

void AutoTurn::Execute() {
	if (m_left)
		m_drive->ArcadeDrive(0, 0.5, false);
	else
		m_drive->ArcadeDrive(0, -0.5, false);

	m_amount = m_amount - 1;
}

void AutoTurn::End(bool interrupted) { }

bool AutoTurn::IsFinished() { return m_amount <= 0; }