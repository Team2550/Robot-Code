// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
	ConfigureBindings();
	m_drive.SetDefaultCommand(TeleDrive(&m_drive, TeleDrive::Control::kArcade, &m_driverController));
	m_launch.SetDefaultCommand(TeleShoot(&m_launch, &m_driverController));
}

void RobotContainer::ConfigureBindings() { }

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {};

frc2::CommandPtr RobotContainer::GetTestCommand() {};
