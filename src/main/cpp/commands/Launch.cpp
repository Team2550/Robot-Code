#include "commands/Launch.h"

Launch::Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Launch::Initialize() { Delay = 0; }

void Launch::Execute() {
	m_launch->LaunchRing();
	Delay = Delay + 1;
	if (Delay >= 5) {
		m_launch->PushRing();
	}
}

void Launch::End(bool interrupted) { m_launch->Stop(); }

bool Launch::IsFinished() { return false; }