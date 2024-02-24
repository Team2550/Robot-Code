#include "commands/TeleIntake.h"

TeleIntake::TeleIntake(IntakeSubsystem* subsystem, frc::XboxController* controller)
	: m_intake(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleIntake::Initialize() { }

void TeleIntake::Execute() {
	if (m_controller->GetBButton()) {
		m_intake->IntakeRing();
	} else if (m_controller->GetAButton()) {
		wait = wait + 1;
		if (wait >= 15) {
			m_intake->ExpellRing();
		}
	} else if (m_controller->GetXButton()) {
		m_intake->GentleRing();
	} else {
		wait = 0;
		m_intake->StopIntake();
	}
	m_intake->PivotIntake((0.7 * m_controller->GetLeftTriggerAxis()), (0.80 * m_controller->GetRightTriggerAxis()));
}

void TeleIntake::End(bool interrupted) { }

bool TeleIntake::IsFinished() { return false; }