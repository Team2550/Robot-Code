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

	if (m_controlType == TeleDrive::Control::kMecanum) {
		m_drive->MecanumDrive((m_controller->GetLeftY()), (m_controller->GetLeftX()), (m_controller->GetRightX()));
	}

	if (m_controlType == TeleDrive::Control::kMecanumTank) {
		m_drive->MecanumTankDrive((m_controller->GetRightY()), (m_controller->GetRightX()), (m_controller->GetLeftY()),
			(m_controller->GetLeftX()));
	}
}

void TeleDrive::End(bool interrupted) { }

bool TeleDrive::IsFinished() { return false; }