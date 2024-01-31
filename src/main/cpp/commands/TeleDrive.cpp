#include "commands/TeleDrive.h"

TeleDrive::TeleDrive(DriveSubsystem* subsystem, TeleDrive::Control controlType, double left, double right)
	: m_drive(subsystem)
	, m_controlType(controlType) {
	AddRequirements({ subsystem });
}

void TeleDrive::Initialize() { }

void TeleDrive::Execute() {

	if (m_controlType == TeleDrive::Control::kTank) {
		m_drive->TankDrive((m_driverController.GetLeftY()), (m_driverController.GetRightY()));
	}

	if (m_controlType == TeleDrive::Control::kArcade) {
		m_drive->ArcadeDrive((m_driverController.GetLeftY()), (m_driverController.GetRightX()));
	}
}

void TeleDrive::End(bool interrupted) { }

bool TeleDrive::IsFinished() { return false; }