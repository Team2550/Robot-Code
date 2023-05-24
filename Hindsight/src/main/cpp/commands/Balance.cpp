#include "commands/Balance.h"

Balance::Balance(DriveSubsystem* subsystem)
	: m_drive(subsystem) {
	AddRequirements({ subsystem });
}

void Balance::Initialize() { }

void Balance::Execute() { }

void Balance::End(bool interrupted) { }

bool Balance::IsFinished() { return false; }