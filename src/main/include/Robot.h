// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandScheduler.h>

#include <optional>

#include "RobotContainer.h"

class Robot : public frc::TimedRobot {
public:
	/**
	 * @brief Runs on robot power up.
	 */
	void RobotInit() override;
	/**
	 * @brief Runs on Timed robot power up.
	 */
	void RobotPeriodic() override;

	void DisabledInit() override;
	void DisabledPeriodic() override;
	void DisabledExit() override;

	/**
	 * @brief Runs on autonomus start.
	 */
	void AutonomousInit() override;
	/**
	 * @brief Runs on Timed robot when auto is enabled.
	 */
	void AutonomousPeriodic() override;
	/**
	 * @brief Runs when auto is finished.
	 */
	void AutonomousExit() override;

	/**
	 * @brief Runs on teleop start.
	 */
	void TeleopInit() override;
	/**
	 * @brief Runs on Timed robot when teleop is enabled.
	 */
	void TeleopPeriodic() override;
	/**
	 * @brief Runs when teleop is finished.
	 */
	void TeleopExit() override;

	void TestInit() override;
	void TestPeriodic() override;
	void TestExit() override;

private:
	/**
	 * @brief Sendable chooser used to select which auto is run,
	 *
	 * Runs either the regular autonomus command in the sequence, or no auto.
	 */
	frc::SendableChooser<std::string> m_chooser;
	const std::string kDefaultAuto = "Default";
	const std::string kNoAuto = "No Auto";
	std::string m_autoSelected;
	std::optional<frc2::CommandPtr> m_autonomousCommand;

	RobotContainer m_container;
};