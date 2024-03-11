#include "commands/AutoHand.h"

AutoHand::AutoHand(ManipulatorSubsystem* subsytem, bool open, int amount)
	: m_manipulator(subsytem)
	, m_open(open)
	, m_amount(amount) {
	AddRequirements({ subsytem });
}

void AutoHand::Initialize() { }

void AutoHand::Execute() {
	if (m_open) {
		m_manipulator->ArmRelease();
	} else {
		m_manipulator->ArmGrab();
	}

	m_amount = m_amount - 1;
}

void AutoHand::End(bool interrupted) { }

bool AutoHand::IsFinished() { return m_amount <= 0; }