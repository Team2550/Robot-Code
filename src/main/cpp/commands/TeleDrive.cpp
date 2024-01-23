#include "commands/TeleDrive.h"

TeleDrive::TeleDrive(DriveSubsystem* subsystem, TeleDrive::Control controlType, frc::XboxController* controller)
	: m_drive(subsystem)
	, m_controlType(controlType)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleDrive::Initialize() { }

void TeleDrive::Execute() {

	if (m_controlType == TeleDrive::Control::kTank) {
		m_drive->TankDrive((m_controller->GetLeftY()), (m_controller->GetRightY()));
	}

	if (m_controlType == TeleDrive::Control::kArcade) {
		m_drive->ArcadeDrive((m_controller->GetLeftY()), (m_controller->GetRightX()));
	}

}

void TeleDrive::End(bool interrupted) { }

bool TeleDrive::IsFinished() { return false; }