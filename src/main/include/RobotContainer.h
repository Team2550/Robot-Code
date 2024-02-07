// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Trigger.h>
#include <units/angle.h>

#include "Constants.h"
#include "commands/AutoDrive.h"
#include "commands/AutoIntake.h"
#include "commands/AutoLaunch.h"
#include "commands/AutoTurn.h"
#include "commands/TeleDrive.h"
#include "commands/TeleIntake.h"
#include "commands/TeleShoot.h"
#include "subsystems/DriveSubsystem.h"
#include "subsystems/IntakeSubsystem.h"
#include "subsystems/LaunchSubsystem.h"

class RobotContainer {
public:
	RobotContainer();

	frc2::CommandPtr GetLeftAutonomous();
	frc2::CommandPtr GetMiddleAutonomous();
	frc2::CommandPtr GetRightAutonomous();

	frc2::CommandPtr GetTestCommand();

private:
	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };

	// The robot's subsystem.
	DriveSubsystem m_drive;
	IntakeSubsystem m_intake;
	LaunchSubsystem m_launch;

	void ConfigureBindings();
	void ConfigureButtonBindings();
};
