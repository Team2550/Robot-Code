#include "commands/Push.h"

Push:Launch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Push:Initialize() { }

void Push::Execute() {
	m_launch->PushRing();
}

void Push::End(bool interrupted) { }

bool Push::IsFinished() { return false; }