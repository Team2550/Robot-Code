// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() { ConfigureBindings(); }

void RobotContainer::ConfigureBindings() {
	ConfigureButtonBindings();
	m_drive.SetDefaultCommand(TeleDrive(&m_drive, TeleDrive::Control::kArcade, &m_driverController));
}

void RobotContainer::ConfigureButtonBindings() {
	m_driverController.A().WhileTrue(Launch(&m_launch).ToPtr());
	m_driverController.B().WhileTrue(Intake(&m_launch).ToPtr());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {};

frc2::CommandPtr RobotContainer::GetTestCommand() {};
