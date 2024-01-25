#include "commands/Launch.h"

Launch::Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Launch::Initialize() { 
	Delay = 0; 
	m_launch->RedLight(true);
}

void Launch::Execute() {
	m_launch->LaunchRing();
	Delay = Delay + 1;
	if (Delay >= 5) {
		m_launch->PushRing();
	}
}

void Launch::End(bool interrupted) { 
	m_launch->Stop(); 
	m_launch->RedLight(false);
}

bool Launch::IsFinished() { return false; }