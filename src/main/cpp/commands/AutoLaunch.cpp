#include "commands/AutoLaunch.h"

AutoLaunch::AutoLaunch(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void AutoLaunch::Initialize() { }

void AutoLaunch::Execute() {
	m_launch->LaunchRing();
	m_launch->PushRing();
}

void AutoLaunch::End(bool interrupted) { m_launch->Stop(); }

bool AutoLaunch::IsFinished() { return false; }