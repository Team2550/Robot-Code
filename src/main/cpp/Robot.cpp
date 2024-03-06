// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
	m_chooser.SetDefaultOption(kMiddleAuto, kMiddleAuto);
	m_chooser.AddOption(kLeftAuto, kLeftAuto);
	m_chooser.AddOption(kRightAuto, kRightAuto);
	m_chooser.AddOption(kStationaryShoot, kStationaryShoot);
	m_chooser.AddOption(kBackup, kBackup);
	m_chooser.AddOption(kNoAuto, kNoAuto);
	frc::SmartDashboard::PutData("Autos", &m_chooser);
	frc::CameraServer::StartAutomaticCapture();
}

void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

void Robot::DisabledInit() { }

void Robot::DisabledPeriodic() { }

void Robot::DisabledExit() { }

void Robot::AutonomousInit() {
	m_autoSelected = m_chooser.GetSelected();
	fmt::print("Auto Selected: {}\n", m_autoSelected);
	frc::SmartDashboard::PutString("Auto Selected:", m_autoSelected);
	if (m_autoSelected == kLeftAuto) {
		m_autonomousCommand = m_container.GetLeftAutonomous();
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else if (m_autoSelected == kMiddleAuto) {
		m_autonomousCommand = m_container.GetMiddleAutonomous();
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else if (m_autoSelected == kRightAuto) {
		m_autonomousCommand = m_container.GetRightAutonomous();
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else if (m_autoSelected == kStationaryShoot) {
		m_autonomousCommand = m_container.GetStationaryShoot();
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else if (m_autoSelected == kBackup) {
		m_autonomousCommand = m_container.GetBackup();
		if (m_autonomousCommand) {
			m_autonomousCommand->Schedule();
		}
	} else {
		// Schedule nothing for 'no auto' option.
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
