#include "commands/ArmHand.h"

ArmHand::ArmHand(ArmHand::Value value, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_value(value) {
	AddRequirements({ subsystem });
}

void ArmHand::Initialize() { }

void ArmHand::Execute() {
	if (m_value == ArmHand::Value::kGrab) {
		m_drive->ArmGrab();
	}
	if (m_value == ArmHand::Value::kRelease) {
		m_drive->ArmRelease();
	}
}

void ArmHand::End(bool interrupted) { }

bool ArmHand::IsFinished() { return false; }