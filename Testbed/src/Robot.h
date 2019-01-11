#ifndef ROBOT_H
#define ROBOT_H

#include <AutoController.h>
#include <WPILib.h>
#include <iostream>
#include <iomanip>
#include "xBox.h"
#include "AutoStrategies.h"
#include "DriveBase.h"
#include "LimitSwitch.h"

class Robot: public IterativeRobot
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

private:
	float speedNormal;
	float speedTurtle;
	float speedBoost;
	float boostDecelerationTime;

	int axisTankLeft;
	int axisTankRight;
	int buttonBoost;
	int buttonTurtle;

	float boostPressTime;

	Preferences *prefs;
	float autoDelay;
	//frc::SendableChooser<const AutoController::PositionOptions*> autoStrategyChooser;
	//const AutoController::InstructionSet* selectedAutoStrategy;
	bool autoStrategyCompleted;
	bool autoStartedBackup;

	Joystick driveController;
	Joystick perifController;
	AutoController autoController;
	Timer timer;

	ADXRS450_Gyro gyroscope;

	DriveBase driveBase;

};

#endif
