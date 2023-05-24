#include "commands/ArmHandTimed.h"

ArmHandTimed::ArmHandTimed(ArmHandTimed::Value value, units::second_t time, DriveSubsystem* subsystem)
	: m_drive(subsystem)
	, m_value(value) {
	AddRequirements({ subsystem });
	m_desiredMs = int(units::millisecond_t(time).value());
}

void ArmHandTimed::Initialize() { }

void ArmHandTimed::Execute() {
	if (m_value == ArmHandTimed::Value::kGrab) {
		m_drive->ArmGrab();
	}
	if (m_value == ArmHandTimed::Value::kRelease) {
		m_drive->ArmRelease();
	}
	m_msOccurred += 20;
}

void ArmHandTimed::End(bool interrupted) { }

bool ArmHandTimed::IsFinished() { return m_msOccurred >= m_desiredMs; }