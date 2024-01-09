#include "commands/WaitCommand.h"

WaitCommand::WaitCommand(units::second_t time) { m_desiredMs = int(units::millisecond_t(time).value()); }

void WaitCommand::Initialize() { }

void WaitCommand::Execute() {
	m_msOccurred += 20;
}

void WaitCommand::End(bool interrupted) { }

bool WaitCommand::IsFinished() { return m_msOccurred >= m_desiredMs; }