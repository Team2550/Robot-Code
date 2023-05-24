// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Trigger.h>
#include <units/angle.h>

#include "Constants.h"
#include "commands/ArmHand.h"
#include "commands/DriveForward.h"
#include "commands/MoveArm.h"
#include "sequences/BalanceAuto.h"
#include "sequences/Drive.h"
#include "subsystems/DriveSubsystem.h"

class RobotContainer {
public:
	RobotContainer();

	frc2::CommandPtr GetAutonomousCommand();

	frc2::CommandPtr GetTestCommand();

private:
	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };

	// The robot's subsystems.
	DriveSubsystem m_drive;

	void ConfigureBindings();
	void ConfigureButtonBindings();
};
