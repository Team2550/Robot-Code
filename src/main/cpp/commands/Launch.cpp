#include "commands/Launch.h"

Launch::Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Launch::Initialize() { }

void Launch::Execute() {
	m_launch->LaunchRing();
	m_launch->PushRing();
}

void Launch::End(bool interrupted) { m_launch->Stop(); }

bool Launch::IsFinished() { return false; }