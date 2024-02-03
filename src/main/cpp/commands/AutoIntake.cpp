#include "commands/AutoIntake.h"

AutoIntake::AutoIntake(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void AutoIntake::Initialize() { }

void AutoIntake::Execute() { m_launch->IntakeRing(); }

void AutoIntake::End(bool interrupted) { m_launch->Stop(); }

bool AutoIntake::IsFinished() { return false; }