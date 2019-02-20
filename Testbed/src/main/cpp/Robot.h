#ifndef ROBOT_H
#define ROBOT_H

#include "AutoController.h"
#include <frc/Commands/Command.h>
#include <frc/Commands/Scheduler.h>
#include <frc/LiveWindow/LiveWindow.h>
#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/WPILib.h>
#include <iostream>
#include <iomanip>
#include "xBox.h"
#include "AutoStrategies.h"
#include "UDP-Receiver.h"
#include "LimitSwitch.h"
#include "AutoAim.h"
#include "Grabber.h"
#include "Winch.h"
#include "DriveBase.h"
#include "Manipulator.h"

class Robot: public IterativeRobot
{
	AutoController autoController; //+
public:

	enum Position { LEFT, RIGHT };

	Robot();
	~Robot();
	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void UpdatePreferences();
//private:
	float speedNormal;
	float speedTurtle;
	float speedBoost;
	float boostDecelerationTime;

	int axisTankLeft;
	int axisTankRight;
	int buttonBoost;
	int buttonTurtle;
	int buttonAutoAim;
	int buttonWinchForwards;
	int buttonWinchBackwards;
	int buttonHandGrab;
	int buttonArmGrab;
	int buttonFeedHatchExtend;
	int buttonFeedHatchRetract;
	int buttonClimbGrabToggle;
	int buttonClimbGrab;
	int buttonClimbRelease;

	int perifControllerPOV = perifController.GetPOV();
	int driveControllerPOV = driveController.GetPOV();

	int climbGrabToggleCount;
	int feedHatchToggleCount;

	float boostPressTime;

	Preferences *prefs;
	float autoDelay;

	bool autoStrategyCompleted;
	bool autoStartedBackup;
	bool autoAimOn = true;
	bool autoAimOff = false;

	frc::SendableChooser<bool*> autoAimChooser;
	bool *autoAimToggle;
	frc::SendableChooser<const AutoController::InstructionSet*> autoStrategyChooser; //+
	const AutoController::InstructionSet* selectedAutoStrategy; //+

	frc::Compressor compressor;
	
	PowerDistributionPanel pdp;

	Joystick driveController;
	Joystick perifController;
	Timer timer;
	//Timer UDPAgeTimer;
	UDP_Receiver udpReceiver;

	ADXRS450_Gyro gyroscope;

	DriveBase driveBase;
	AutoAim autoAim;
	//AutoController autoController;
	Winch winch;
	Grabber grabber;
	Manipulator manipulator;
};

#endif
