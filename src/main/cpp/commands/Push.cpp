#include "commands/Push.h"

Push::Push(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Push::Initialize() { }

void Push::Execute() { m_launch->PushRing(); }

void Push::End(bool interrupted) { m_launch->Stop(); }

bool Push::IsFinished() { return false; }