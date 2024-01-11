#include "commands/Push.h"

Push:Launch(DriveSubsystem* subsytem) 
	: m_drive(subsytem) {
	AddRequirements({ subsytem });
}

void Push:Initialize() { }

void Push::Execute() {
	m_drive->PushRing();
}

void Push::End(bool interrupted) { }

bool Push::IsFinished() { return false; }