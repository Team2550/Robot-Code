#include "commands/Launch.h"

Launch:Launch(DriveSubsystem* subsytem) 
	: m_drive(subsytem) {
	AddRequirements({ subsytem });
}

void Launch:Initialize() { }

void Launch::Execute() {
	m_drive->LaunchRing();
	m_drive->PushRing();
}

void Launch::End(bool interrupted) { }

bool Launch::IsFinished() { return false; }