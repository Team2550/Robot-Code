#include "commands/TeleClimb.h"

TeleClimb::TeleClimb(ClimbSubsystem* subsystem, frc::XboxController* controller)
	: m_climber(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleClimb::Initialize() { }

void TeleClimb::Execute() {
    
}

void TeleClimb::End(bool interrupted) { }

bool TeleClimb::IsFinished() { return false; }