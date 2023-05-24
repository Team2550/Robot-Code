#include "commands/MoveArm.h"

MoveArm::MoveArm(double upTrigger, double downTrigger, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, upTrigger(upTrigger)
	, downTrigger(downTrigger) {
	AddRequirements({ subsystem });
}

void MoveArm::Initialize() { }

void MoveArm::Execute() {
	m_drive->MoveArm(upTrigger);
	m_drive->MoveArm(downTrigger);
}

void MoveArm::End(bool interrupted) { m_drive->MoveArm(0.0); }

bool MoveArm::IsFinished() { return false; }