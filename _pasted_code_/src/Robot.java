/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <RobotDrive.h>
#include <VictorSP.h>
#include <XboxController.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot : public frc::IterativeRobot {
public:
	Robot() : frontLeft(0), frontRight(1), backLeft(2), backRight(3),
	          //robotDrive(frontLeft, backLeft, frontRight, backRight),
	          controller(0) {
	}
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

		frontLeft.SetInverted(true);
		backLeft.SetInverted(false);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString(
		// 		"Auto Selector", kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		float backLeftPower = 0, backRightPower = 0,
		      frontLeftPower = 0, frontRightPower = 0;

		float leftX = controller.GetX(frc::GenericHID::kLeftHand);
		float rightX = controller.GetX(frc::GenericHID::kRightHand);
		float leftY = controller.GetY(frc::GenericHID::kLeftHand);

		leftX = fabs(leftX) < 0.2 ? 0 : leftX / 2;
		leftY = fabs(leftY) < 0.2 ? 0 : -leftY / 2;
		rightX = fabs(rightX) < 0.2 ? 0 : rightX / 2;

		// Adjust values for strafing
		int strafeMult = 2;
		backLeftPower -= leftX * strafeMult; //* 1.3;
		backRightPower += leftX * strafeMult;
		frontLeftPower += leftX * strafeMult;
		frontRightPower -= leftX * strafeMult;

		// Adjust values for normal (forwards and backwards) motion
		backLeftPower += leftY; // * 1.7;
		backRightPower += leftY;
		frontLeftPower += leftY;
		frontRightPower += leftY;

		// Adjust values for rotation
		backLeftPower += rightX;
		backRightPower -= rightX;
		frontLeftPower += rightX;
		frontRightPower -= rightX;

		backLeft.Set(backLeftPower);
		backRight.Set(backRightPower);
		frontLeft.Set(frontLeftPower);
		frontRight.Set(frontRightPower);
	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
	//frc::RobotDrive robotDrive;
	frc::VictorSP frontLeft;
	frc::VictorSP frontRight;
	frc::VictorSP backLeft;
	frc::VictorSP backRight;
	frc::XboxController controller;
};

START_ROBOT_CLASS(Robot)
