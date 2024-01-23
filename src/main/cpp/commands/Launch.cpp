#include "commands/Launch.h"

Launch::Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Launch::Initialize() { Delay = 0; }

// Note: Launch and Push Motors are missnamed, Fix this.
void Launch::Execute() {
	m_launch->PushRing();
	Delay = Delay + 1;
	if (Delay >= 50) {
		m_launch->LaunchRing();
	}
}

void Launch::End(bool interrupted) { m_launch->Stop(); }

bool Launch::IsFinished() { return false; }