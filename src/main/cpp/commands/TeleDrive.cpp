#include "commands/TeleDrive.h"

TeleDrive::TeleDrive(DriveSubsystem* subsystem, TeleDrive::Control controlType, double left, double right)
	: m_drive(subsystem)
	, m_controlType(controlType)
	, m_left(left)
	, m_right(right) {
	AddRequirements({ subsystem });
}

void TeleDrive::Initialize() { }

void TeleDrive::Execute() {

	if (m_controlType == TeleDrive::Control::kTank) {
		m_drive->TankDrive((m_left), (m_right));
	}

	if (m_controlType == TeleDrive::Control::kArcade) {
		m_drive->ArcadeDrive((m_left), (m_right));
	}
}

void TeleDrive::End(bool interrupted) { }

bool TeleDrive::IsFinished() { return false; }