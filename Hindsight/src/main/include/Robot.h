// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "cameraserver/CameraServer.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/CommandScheduler.h>

#include <optional>

#include "RobotContainer.h"

class Robot : public frc::TimedRobot {
public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void DisabledExit() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void AutonomousExit() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TeleopExit() override;
	void TestInit() override;
	void TestPeriodic() override;
	void TestExit() override;

private:
	frc::SendableChooser<std::string> m_chooser;
	const std::string kDefaultAuto = "Default";
	const std::string kNoAuto = "No Auto";
	std::string m_autoSelected;
	std::optional<frc2::CommandPtr> m_autonomousCommand;
	std::optional<frc2::CommandPtr> m_testCommand;

	RobotContainer m_container;
};