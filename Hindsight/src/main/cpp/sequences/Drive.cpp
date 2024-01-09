#include "sequences/Drive.h"

Drive::Drive(DriveSubsystem* subsystem)
	: m_drive(subsystem) {
	AddRequirements({ subsystem });
}

void Drive::Initialize() { }

void Drive::Execute() {

	// Arcade style movement
	m_drive->MecanumDrive(
		((m_driverController.GetLeftY())), ((m_driverController.GetLeftX())), ((m_driverController.GetRightX())));

	/*
	// Tank style movement
	m_drive->MecanumTankDrive(m_driverController.GetRightY(), m_driverController.GetRightX(),
		m_driverController.GetLeftY(), m_driverController.GetLeftX());
	*/
}

void Drive::End(bool interrupted) { }

bool Drive::IsFinished() { return false; }