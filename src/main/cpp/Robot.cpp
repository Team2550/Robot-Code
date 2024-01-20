// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
	m_chooser.SetDefaultOption(kDefaultAuto, kDefaultAuto);
	m_chooser.AddOption(kNoAuto, kNoAuto);
	frc::SmartDashboard::PutData("Autos", &m_chooser);
}

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

void Robot::DisabledInit() { }

void Robot::DisabledPeriodic() { }

void Robot::DisabledExit() { }

void Robot::AutonomousInit() {
	m_autoSelected = m_chooser.GetSelected();
	fmt::print("Auto Selected: {}\n", m_autoSelected);
	frc::SmartDashboard::PutString("Auto Selected:", m_autoSelected);
	m_autonomousCommand = m_container.GetAutonomousCommand();
	if (m_autoSelected == kDefaultAuto) {
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else {
	}
}

void Robot::AutonomousPeriodic() { }

void Robot::AutonomousExit() { }

void Robot::TeleopInit() {
	if (m_autonomousCommand) {
		// Make sure the auto command isn't still running (this would cause a conflict!)
		m_autonomousCommand->Cancel();
	}
}

void Robot::TeleopPeriodic() { }

void Robot::TeleopExit() { }

void Robot::TestInit() { }

void Robot::TestPeriodic() { }

void Robot::TestExit() { }

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
