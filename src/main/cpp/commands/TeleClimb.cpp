#include "commands/TeleClimb.h"

TeleClimb::TeleClimb(ClimbSubsystem* subsystem, frc::XboxController* controller)
	: m_climber(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleClimb::Initialize() { }

void TeleClimb::Execute() {
	m_climber->Climb((m_controller->GetLeftTriggerAxis()), m_controller->GetRightTriggerAxis());
}

void TeleClimb::End(bool interrupted) { }

bool TeleClimb::IsFinished() { return false; }