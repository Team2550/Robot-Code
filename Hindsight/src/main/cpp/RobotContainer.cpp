// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() { ConfigureBindings(); }

void RobotContainer::ConfigureBindings() {
	m_differentialDrive.SetDefaultCommand(Drive(&m_differentialDrive, kTank).ToPtr());
	m_mecanumDrive.SetDefaultCommand(Drive(&m_mecanumDrive, kMecanum).ToPtr());
	ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() { 
	m_driverController.B().WhileTrue(m_differentialDrive.)
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {};

frc2::CommandPtr RobotContainer::GetTestCommand() {};