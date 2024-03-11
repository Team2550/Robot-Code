// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
	ConfigureBindings();
	m_drive.SetDefaultCommand(TeleDrive(&m_drive, TeleDrive::Control::kArcade, &m_driverController));
	m_manipulator.SetDefaultCommand(TeleArm(&m_manipulator, &m_driverController));
}

void RobotContainer::ConfigureBindings() { }

frc2::CommandPtr RobotContainer::GetBackup() { return frc2::cmd::Sequence(AutoDrive(&m_drive, -0.5, 25).ToPtr()); }

frc2::CommandPtr RobotContainer::GetLowerPlace() {
	return frc2::cmd::Sequence(AutoDrive(&m_drive, -0.6, 7).ToPtr(), AutoHand(&m_manipulator, true, 40).ToPtr(),
		AutoDrive(&m_drive, -0.5, 70).ToPtr());
}

frc2::CommandPtr RobotContainer::GetTestCommand() {};
