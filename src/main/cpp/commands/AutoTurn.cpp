#include "commands/AutoTurn.h"

AutoTurn::AutoTurn(DriveSubsystem* subsytem, bool left, double amount, frc::DriverStation* ds)
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

	m_drive->ResetAngle();
}

void AutoTurn::Execute() {
	if (m_left)
		m_drive->ArcadeDrive(0, 0.5, false);
	else
		m_drive->ArcadeDrive(0, -0.5, false);
}

void AutoTurn::End(bool interrupted) { }

bool AutoTurn::IsFinished() {
	if (m_left)
		return m_drive->GetCurrentAngle() <= (360-m_amount);
	else
		return m_drive->GetCurrentAngle() >= m_amount;
}