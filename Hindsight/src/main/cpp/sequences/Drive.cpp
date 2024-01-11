#include "sequences/Drive.h"

Drive::Drive(DriveSubsystem* subsystem, int controlType)
	: m_drive(subsystem) 
	, m_controlType(controlType) {
	AddRequirements({ subsystem, controlType });
}

void Drive::Initialize() { }

void Drive::Execute() {

	if (m_controlType == 0) { // Tank Drive Controls
		m_drive->TankDrive(
		(m_driverController.GetLeftY()),(m_driverController.GetRightY()));
	}

	if (m_controlType == 1) { // Arcade Drive Controls
		m_drive->ArcadeDrive(
		(m_driverController.GetLeftY()),(m_driverController.GetRightX()));
	}

	if (m_controlType == 2) { // Mecanum Drive Controls
		m_drive->MecanumDrive(
		(m_driverController.GetLeftY()), (m_driverController.GetLeftX()), (m_driverController.GetRightX()));
	}

	if (m_controlType == 3) { // Mecanum "Tank" Drive Controls
		m_drive->MecanumTankDrive(m_driverController.GetRightY(), m_driverController.GetRightX(),
		m_driverController.GetLeftY(), m_driverController.GetLeftX());
	}

}

void Drive::End(bool interrupted) { }

bool Drive::IsFinished() { return false; }