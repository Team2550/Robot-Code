#include "commands/TeleIntake.h"

TeleIntake::TeleIntake(IntakeSubsystem* subsystem, frc::XboxController* controller)
	: m_intake(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleIntake::Initialize() { }

void TeleIntake::Execute() {
	if (m_controller->GetXButton()) {
		m_intake->IntakeRing();
	} else if (m_controller->GetYButton()) {
		m_intake->ExpellRing();
	} else {
		m_intake->StopInake();
	}
	m_intake->PivotIntake(m_controller->GetLeftTriggerAxis(), m_controller->GetRightTriggerAxis());
}

void TeleIntake::End(bool interrupted) { }

bool TeleIntake::IsFinished() { return false; }