#include "commands/TeleDrive.h"

TeleDrive::TeleDrive(DriveSubsystem* subsystem, TeleDrive::Control controlType, double left, double right)
	: m_drive(subsystem)
	, m_controlType(controlType) {
	AddRequirements({ subsystem });
}

void TeleDrive::Initialize() { }

void TeleDrive::Execute() {
	if (m_driverController.GetLeftBumper()) {
		m_speedMult = 1.0;
	} else {
		m_speedMult = 0.75;
	}

	if (m_controlType == TeleDrive::Control::kTank) {
		m_drive->TankDrive(
			-(m_speedMult * (m_driverController.GetLeftY())), (m_speedMult * (m_driverController.GetRightY())), true);
	}

	if (m_controlType == TeleDrive::Control::kArcade) {
		m_drive->ArcadeDrive(
			-(m_speedMult * (m_driverController.GetLeftY())), (m_speedMult * (m_driverController.GetRightX())), true);
	}
}

void TeleDrive::End(bool interrupted) { }

bool TeleDrive::IsFinished() { return false; }