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
#include "subsystems/DriveSubsystem.h"
#include "subsystems/LaunchSubsystem.h"

class RobotContainer {
public:
    enum Control {kTank, kArcade, kMecanum, kMecanumTank}

	RobotContainer();

	/**
     * @brief Sets the control type used by the robot
     *
     * Control Types
     * =============
     *
     * kTank
     * kArcade
     * kMecanum
     * kMecanumTank
     *
     * @param[in] controlType Accepts one of 4 values to specify which control scheme is used.
     */
	void SetControlType(Control controlType);

	frc2::CommandPtr GetAutonomousCommand();

	frc2::CommandPtr GetTestCommand();

private:
    RobotContainer::Control m_controlType;

	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };

	// The robot's subsystem.
	DriveSubsystem m_drive;
	LaunchSubsystem m_launch;

	void ConfigureBindings();
	void ConfigureButtonBindings();
};
