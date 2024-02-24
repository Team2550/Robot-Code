#include "commands/AutoPickup.h"

AutoPickup::AutoPickup(IntakeSubsystem* intakeSubsystem, DriveSubsystem* driveSubsystem, int amount)
	: m_drive(driveSubsystem)
	, m_intake(intakeSubsystem)
	, m_amount(amount) {
	AddRequirements({ intakeSubsystem });
	AddRequirements({ driveSubsystem });
}

void AutoPickup::Initialize() { }

void AutoPickup::Execute() {
	m_intake->IntakeRing();
	m_drive->ArcadeDrive(-0.5, 0, true);
	m_amount = m_amount - 1;
}

void AutoPickup::End(bool interrupted) {
	m_intake->StopIntake();
	m_drive->ArcadeDrive(0, 0, true);
}

bool AutoPickup::IsFinished() { return m_amount <= 0; }