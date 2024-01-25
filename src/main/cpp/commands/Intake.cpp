#include "commands/Intake.h"

Intake::Intake(LaunchSubsystem* subsytem)
	: m_launch(subsytem) {
	AddRequirements({ subsytem });
}

void Intake::Initialize() { m_launch->BlueLight(true); }

void Intake::Execute() { 
	m_launch->IntakeRing(); 
}

void Intake::End(bool interrupted) { 
	m_launch->Stop(); 
	m_launch->BlueLight(false);
}

bool Intake::IsFinished() { return false; }