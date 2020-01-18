#ifndef ROBOT_H
#define ROBOT_H

#include <frc/Commands/Command.h>
#include <cameraserver/CameraServer.h>
#include <frc/Commands/Scheduler.h>
#include <frc/LiveWindow/LiveWindow.h>
#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/Preferences.h>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <iostream>
#include <iomanip>
#include "Xbox.h"
#include "Input.h"
#include "UDPReceiver.h"
#include "DriveBase.h"

class Robot: public TimedRobot
{
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
	int buttonFeedHatchToggle;
	int buttonClimbGrabToggle;

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
	
	PowerDistributionPanel pdp;

	Xbox inputController;
	Timer timer;
	UDPReceiver udpReceiver;

	ADXRS450_Gyro gyroscope;

	DriveBase driveBase;
};

#endif
