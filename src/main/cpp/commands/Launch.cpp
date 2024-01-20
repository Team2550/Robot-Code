#include "commands/Launch.h"

Launch::Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Launch::Initialize() { }

void Launch::Execute() { m_launch->LaunchRing(); }

void Launch::End(bool interrupted) { }

bool Launch::IsFinished() { return false; }