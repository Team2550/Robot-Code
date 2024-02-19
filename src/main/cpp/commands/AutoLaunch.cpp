#include "commands/AutoLaunch.h"

AutoLaunch::AutoLaunch(LaunchSubsystem* subsytem, int amount)
	: m_launch(subsytem)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoLaunch::Initialize() { }

void AutoLaunch::Execute() {
	m_launch->LaunchRing();
	m_launch->PushRing();
	m_amount = m_amount - 1;
}

void AutoLaunch::End(bool interrupted) { m_launch->Stop(); }

bool AutoLaunch::IsFinished() { return m_amount <= 0; }