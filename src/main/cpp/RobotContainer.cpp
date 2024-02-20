// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
	ConfigureBindings();
	m_drive.SetDefaultCommand(TeleDrive(&m_drive, TeleDrive::Control::kArcade, &m_driverController));
	m_climber.SetDefaultCommand(TeleClimb(&m_climber, &m_driverController));

	m_launch.SetDefaultCommand(TeleShoot(&m_launch, &m_manipulatorController));
	m_intake.SetDefaultCommand(TeleIntake(&m_intake, &m_manipulatorController));
}

void RobotContainer::ConfigureBindings() { }

// For these autos it is assumed the robot is starting aligned with the speaker
// Thus, Fire ring, turn to face line (if needed), leave starting zone.
frc2::CommandPtr RobotContainer::GetLeftAutonomous() {
	return frc2::cmd::Sequence(
		AutoLaunch(&m_launch, &m_intake, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoTurn(&m_drive, false, 15, ds).ToPtr(),
		AutoDrive(&m_drive, false, 25).ToPtr());
};
frc2::CommandPtr RobotContainer::GetMiddleAutonomous() {
	return frc2::cmd::Sequence(
		AutoLaunch(&m_launch, &m_intake, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoDrive(&m_drive, false, 25).ToPtr(),
		AutoPivot(&m_intake, false, 10).ToPtr(),
		AutoPickup(&m_intake, &m_drive, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoPivot(&m_intake, true, 10).ToPtr(),
		AutoDrive(&m_drive, false, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoLaunch(&m_launch, &m_intake, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoDrive(&m_drive, true, 20).ToPtr());
};
frc2::CommandPtr RobotContainer::GetRightAutonomous() {
	return frc2::cmd::Sequence(
		AutoLaunch(&m_launch, &m_intake, 30).ToPtr(),
		frc2::cmd::Wait(0.5_s),
		AutoTurn(&m_drive, true, 15, ds).ToPtr(),
		AutoDrive(&m_drive, false, 25).ToPtr());
};

frc2::CommandPtr RobotContainer::GetTestCommand() {};
