#include "commands/AutoLaunch.h"

AutoLaunch::AutoLaunch(LaunchSubsystem* launchSubsystem, IntakeSubsystem* intakeSubsystem, int amount)
	: m_launch(launchSubsystem)
	, m_intake(intakeSubsystem)
	, m_amount(amount) {
	AddRequirements({ launchSubsystem });
	AddRequirements({ intakeSubsystem });
}

void AutoLaunch::Initialize() { }

void AutoLaunch::Execute() {
	m_intake->ExpellRing();
	m_launch->LaunchRing();
	m_launch->PushRing();
	m_amount = m_amount - 1;
}

void AutoLaunch::End(bool interrupted) {
	m_launch->Stop();
	m_intake->StopIntake();
}

bool AutoLaunch::IsFinished() { return m_amount <= 0; }