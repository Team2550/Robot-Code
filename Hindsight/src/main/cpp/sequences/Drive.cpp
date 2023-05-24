#include "sequences/Drive.h"

Drive::Drive(DriveSubsystem* subsystem)
	: m_drive(subsystem) {
	AddRequirements({ subsystem });
}

void Drive::Initialize() { m_speedMult = 0.70; }

void Drive::Execute() {
	// Smartdashboard outputs for controls
	frc::SmartDashboard::PutNumber("Forward speed:", -m_driverController.GetLeftY());
	frc::SmartDashboard::PutNumber("Turning speed:", -m_driverController.GetRightX());

	// Movement + Turbo toggle
	if (m_driverController.GetRightBumper() == 1) {
		frc::SmartDashboard::PutString("Turbo status:", "✅");
		m_drive->ArcadeDrive(((m_driverController.GetLeftY())), ((m_driverController.GetRightX())));
	} else {
		frc::SmartDashboard::PutString("Turbo status:", "❌");
		m_drive->ArcadeDrive(
			((m_driverController.GetLeftY()) * m_speedMult), ((m_driverController.GetRightX()) * m_speedMult));
	}

	// Arm movement
	if (m_armController.GetLeftTriggerAxis() < m_armController.GetRightTriggerAxis()) {
		m_drive->MoveArm(-m_armController.GetRightTriggerAxis());
		frc::SmartDashboard::PutString("Arm status:", "MOVING UP");
	} else {
		if (m_armController.GetLeftTriggerAxis() > m_armController.GetRightTriggerAxis()) {
			m_drive->MoveArm(m_armController.GetLeftTriggerAxis());
			m_drive->DriveWinch(-0.2);
			frc::SmartDashboard::PutString("Arm status:", "MOVING DOWN");
		};
	}
	if (m_armController.GetLeftTriggerAxis() == m_armController.GetRightTriggerAxis()) {
		m_drive->MoveArm(0.0);
		m_drive->DriveWinch(0);
		frc::SmartDashboard::PutString("Arm status:", "NOT MOVING");
	}

	// Winch when button
	if (m_driverController.GetAButton() == 1 || m_armController.GetXButton() == 1) {
		m_drive->DriveWinch(-0.5);
	} else if (m_driverController.GetBButton() == 1) {
		m_drive->DriveWinch(-1.0);
	}

	// Clear winch if no input & arm is not moving down.
	if ((m_driverController.GetAButton() == 0 && m_driverController.GetBButton() == 0
			&& m_armController.GetXButton() == 0)
		&& (m_armController.GetLeftTriggerAxis() < m_armController.GetRightTriggerAxis())) {
		m_drive->DriveWinch(0);
	}

	// This is labled ArmTask, but it really is HandTask
	if (m_armController.GetAButton() == 1 && m_armController.GetBButton() == 0) {
		m_drive->ArmRelease();
	}
	if (m_armController.GetBButton() == 1 && m_armController.GetAButton() == 0) {
		m_drive->ArmGrab();
	}
	if (m_armController.GetBButton() == 0 && m_armController.GetAButton() == 0) {
		m_drive->ArmRest();
	}
}

void Drive::End(bool interrupted) { }

bool Drive::IsFinished() { return false; }