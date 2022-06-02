#ifndef ROBOT_H
#define ROBOT_H

#include <cameraserver/CameraServer.h>
#include <frc/ADXRS450_Gyro.h>
#include <frc/PowerDistribution.h>
#include <frc/Preferences.h>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <frc/Timer.h>
#include <frc/commands/Command.h>
#include <frc/commands/Scheduler.h>
#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iomanip>
#include <iostream>
// Not all inputs are in use, but makes for very fast adaptations.
#include "FlightStick.h"
#include "Input.h"
#include "Xbox.h"

#include "DriveBase.h"
#include "Intake.h"
#include "UDPReceiver.h"

class Robot : public TimedRobot {
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

	frc::SendableChooser<bool *> autoAimChooser;
	bool *autoAimToggle;

	PowerDistribution pdp;

	FlightStick inputController;
	Timer timer;
	UDPReceiver udpReceiver;

	ADXRS450_Gyro gyroscope;

	Intake intake;
	DriveBase driveBase;
};

#endif
