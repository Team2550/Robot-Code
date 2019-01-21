#ifndef ROBOT_H
#define ROBOT_H

#include <AutoController.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include <iostream>
#include <iomanip>
#include "xBox.h"
#include "AutoStrategies.h"
#include "UDP-Receiver.h"
#include "DriveBase.h"
#include "LimitSwitch.h"
#include "AutoAim.h"

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
	void autoAimOn();
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

	float boostPressTime;

	Preferences *prefs;
	float autoDelay;
	//frc::SendableChooser<const AutoController::PositionOptions*> autoStrategyChooser;
	//const AutoController::InstructionSet* selectedAutoStrategy;

	//std::unique_ptr<frc::Command> autoAimCommand;
	//frc::SendableChooser<frc::Command*> autoAimChooser;

	bool autoStrategyCompleted;
	bool autoStartedBackup;
	bool autoAimToggle;
	PowerDistributionPanel pdp;

	Joystick driveController;
	Joystick perifController;
	AutoController autoController;
	Timer timer;
	//Timer UDPAgeTimer;
	UDP_Receiver udpReceiver;

	ADXRS450_Gyro gyroscope;

	DriveBase driveBase;


	AutoAim autoAim;

};

#endif
