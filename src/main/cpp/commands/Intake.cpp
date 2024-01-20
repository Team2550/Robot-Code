#include "commands/Intake.h"

Intake::Intake(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Intake::Initialize() { }

void Intake::Execute() { m_launch->IntakeRing(); }

void Intake::End(bool interrupted) { }

bool Intake::IsFinished() { return false; }