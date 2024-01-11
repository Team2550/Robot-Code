// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
    this->SetControlType(RobotContainer::Control::kArcade);
    ConfigureBindings();
}

void RobotContainer::SetControlType(RobotContainer::Control control_type) {
    if m_controlType == control_type {
        return 1;
    } else {
        m_controlType = control_type;
        return 0;
    }
}

void RobotContainer::ConfigureBindings() {

    ConfigureButtonBindings();

    if (m_controlType == RobotContainer::kTank) {
        m_drive.SetDefaultCommand(frc2::cmd::Run(
            [this] {
                m_drive.TankDrive((m_driverController.GetLeftY()), (m_driverController.GetRightY()));
            },
            {&m_drive}));
    }

    if (m_controlType == RobotContainer::kArcade) {
        m_drive.SetDefaultCommand(frc2::cmd::Run(
            [this] {
                m_drive.ArcadeDrive((m_driverController.GetLeftY()), (m_driverController.GetRightX()));
            },
            {&m_drive}));
    }

    if (m_controlType == RobotContainer::kMecanum) {
        m_drive.SetDefaultCommand(frc2::cmd::Run(
            [this] {
        	    m_drive.MecanumDrive((m_driverController.GetLeftY()), (m_driverController.GetLeftX()),
        	                         (m_driverController.GetRightX()));
        	},
        	{&m_drive}));
   	}

    if (m_controlType == RobotContainer::kMecanumTank) {
        m_drive.SetDefaultCommand(frc2::cmd::Run(
            [this] {
    	        m_drive.MecanumTankDrive(m_driverController.GetRightY(), m_driverController.GetRightX(),
    	                                 m_driverController.GetLeftY(), m_driverController.GetLeftX());
    	    },
    	    {&m_drive}));
    }
}

void RobotContainer::ConfigureButtonBindings() { }

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {};

frc2::CommandPtr RobotContainer::GetTestCommand() {};