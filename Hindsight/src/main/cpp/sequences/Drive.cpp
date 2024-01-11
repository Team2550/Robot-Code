#include "sequences/Drive.h"

Drive::Drive(DriveSubsystem* subsystem, Drive::Control controlType)
	: m_drive(subsystem) 
	, m_controlType(controlType) {
	AddRequirements({ subsystem, controlType });
}

void Drive::Initialize() { }

void Drive::Execute() {

	if (m_controlType == Drive::kTank) {
		m_drive->TankDrive(
		(m_driverController.GetLeftY()),(m_driverController.GetRightY()));
	}

	if (m_controlType == Drive::kArcade) {
		m_drive->ArcadeDrive(
		(m_driverController.GetLeftY()),(m_driverController.GetRightX()));
	}

	if (m_controlType == Drive::kMecanum) {
		m_drive->MecanumDrive(
		(m_driverController.GetLeftY()), (m_driverController.GetLeftX()), (m_driverController.GetRightX()));
	}

	if (m_controlType == Drive::kMecanumTank) { 
		m_drive->MecanumTankDrive(m_driverController.GetRightY(), m_driverController.GetRightX(),
		m_driverController.GetLeftY(), m_driverController.GetLeftX());
	}

}

void Drive::End(bool interrupted) { }

bool Drive::IsFinished() { return false; }