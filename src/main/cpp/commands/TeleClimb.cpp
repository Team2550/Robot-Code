#include "commands/TeleClimb.h"

TeleClimb::TeleClimb(ClimbSubsystem* subsystem, frc::XboxController* controller, frc::XboxController* secondController)
	: m_climber(subsystem)
	, m_controller(controller)
	, m_secondController(secondController) {
	AddRequirements({ subsystem });
}

void TeleClimb::Initialize() { }

void TeleClimb::Execute() {
	if (m_secondController->GetStartButton()) {
		m_climber->Climb(m_controller->GetLeftTriggerAxis());
	}
}

void TeleClimb::End(bool interrupted) { }

bool TeleClimb::IsFinished() { return false; }