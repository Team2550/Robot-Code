//This code was made for the FRC 2019 season
//By: Brayton Kerekffy and Travis Albers
#include "Robot.h"

// driver: (int) xBox controller number
// driveBase:  (float) max power, (float) max boost power, (int) left motor port,
//             (int) right motor port

Robot::Robot() : autoAim(this), driveController(0), perifController(1),
				 udpReceiver(),
				 autoController(&driveBase, &gyroscope, this), //+
				 gyroscope(frc::SPI::Port::kOnboardCS0),
				 driveBase(1, 0, 0, 1, 2, 3, 6.07 * M_PI, 512), // Pulses per rotation is set by encoder DIP switch. 512 PPR uses DIP switch configuration 0001.
				 winch(2),
				 grabber(2,3,4,5),
				 manipulator(2,3,4,5)
{
	axisTankLeft = xbox::axis::leftY;
	axisTankRight = xbox::axis::rightY;
	buttonBoost = xbox::btn::rb;
	buttonTurtle = xbox::btn::lb;
	buttonAutoAim = xbox::btn::a;
	autoAimToggle = &autoAimOn;
	buttonWinchForwards = xbox::btn::rb;
	buttonWinchBackwards = xbox::btn::lb;
	buttonClimberGrab = xbox::btn::rightPush;
	buttonClimberRelease = xbox::btn::leftPush;
	buttonGrabHatch = xbox::btn::a;
	buttonReleaseHatch = xbox::btn::x;

	boostPressTime = -999;

	UpdatePreferences();
}

Robot::~Robot()
{

}

void Robot::RobotInit()
{
	std::cout << "Calibrating gyro..." << std::endl;
	gyroscope.Calibrate();
	std::cout << "Gyro calibrated.... This message gets sent regardless of if the Gyro was calibrated or not. I hope it doesn't fail :)" << std::endl;

	//autoAimChooser.AddDefault("Default Auto", new );
	autoAimChooser.AddDefault("Auto Aim On", &autoAimOn);
	autoAimChooser.AddObject("Auto Aim Off", &autoAimOff);
	SmartDashboard::PutData("Auto Aim Toggle", &autoAimChooser);

	driveBase.setReversed(true);

	// Start Video Stream
	// URL is "http://10.25.50.94:8080/"
	CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::AutonomousInit()
{
	UpdatePreferences();

	driveBase.Stop();

	timer.Reset();
	timer.Start();

	
	//+
	if (selectedAutoStrategy != NULL)
	{
		std::cout << "Initializing autonomous" << std::endl;
		autoController.Init(*selectedAutoStrategy);
		autoStrategyCompleted = false;
	}
	else
	{
		std::cout << "Selected strategy is blank" << std::endl;
		autoStrategyCompleted = true;
	}
}

void Robot::AutonomousPeriodic()
{
	/* ========== udpReceiver ========== */
	udpReceiver.checkUDP();
	udpReceiver.clearUDPSocket();

	float data[UDP::DataCount];
	udpReceiver.getUDPData(data);

	printf("X Angle:");
	printf(std::to_string(data[UDP::Index::HorizAngle]).c_str());
	printf(", Dist:");
	printf(std::to_string(data[UDP::Index::Distance]).c_str());
	printf("\n");

	
}

void Robot::TeleopInit()
{
	UpdatePreferences();

	gyroscope.Reset();

	driveBase.Stop();
	driveBase.ResetDistance();
	boostPressTime = -999;


	timer.Reset();
	timer.Start();
}

void Robot::TeleopPeriodic()
{
	/* ========== udpReceiver ========== */
	udpReceiver.checkUDP();
	udpReceiver.clearUDPSocket();

	float data[UDP::DataCount];
	udpReceiver.getUDPData(data);

	printf("X Angle:");
	printf(std::to_string(data[UDP::Index::HorizAngle]).c_str());
	printf(", Dist:");
	printf(std::to_string(data[UDP::Index::Distance]).c_str());
	printf("\n");

	std::cout << "Left: " << std::setw(5) << driveBase.GetLeftDistance() << ' '
	          << "Right: " << std::setw(5) << driveBase.GetRightDistance() << ' '
			  << "Angle: " << std::setw(5) << gyroscope.GetAngle() << std::endl;

	// Drivebase
	// Use D-pad of controller to drive in basic directions

	if(driveController.GetRawButton(buttonAutoAim)){
		autoAim.checkAutoAim();
	}
	else{
		int controllerPOV = driveController.GetPOV();

		if (controllerPOV == 0)
		{
			driveBase.Drive(speedTurtle);
		}
		else if (controllerPOV == 45)
		{
			driveBase.Drive(speedTurtle, 0);
		}
		else if (controllerPOV == 90)
		{
			driveBase.Drive(speedTurtle, -speedTurtle);
		}
		else if (controllerPOV == 135)
		{
			driveBase.Drive(0, -speedTurtle);
		}
		else if (controllerPOV == 180)
		{
			driveBase.Drive(-speedTurtle);
		}
		else if (controllerPOV == 225)
		{
			driveBase.Drive(-speedTurtle, 0);
		}
		else if (controllerPOV == 270)
		{
			driveBase.Drive(-speedTurtle, speedTurtle);
		}
		else if (controllerPOV == 315)
		{
			driveBase.Drive(0, speedTurtle);
		}
		else // No buttons on D-pad being pressed, use joysticks
		{
			float leftSpeed = Utility::Deadzone(-driveController.GetRawAxis(axisTankLeft));
			float rightSpeed = Utility::Deadzone(-driveController.GetRawAxis(axisTankRight));

			float baseSpeed = speedNormal;

			if (driveController.GetRawButton(buttonTurtle)) // Turtle
				baseSpeed = speedTurtle;
			else if (driveController.GetRawButton(buttonBoost)) // Boost
			{
				baseSpeed = speedBoost;
				boostPressTime = timer.Get();
			}
			else if (timer.Get() < boostPressTime + boostDecelerationTime) // Deceleration from boost
				baseSpeed = speedBoost + (speedNormal - speedBoost) * ((timer.Get() - boostPressTime) / boostDecelerationTime);

			driveBase.Drive(leftSpeed * baseSpeed,
							rightSpeed * baseSpeed);
		}
		//Winch
		if(perifController.GetRawButton(buttonWinchForwards))
		{
			winch.climb(true, false);
		}
		else if(perifController.GetRawButton(buttonWinchBackwards))
		{
			winch.climb(false, true);
		}
		else
		{
			winch.climb(false, false);
		}
		//Grabber
		if(perifController.GetRawButton(buttonClimberGrab))
		{
			grabber.armGrab();
			grabber.handGrab();
		}
		if(perifController.GetRawButton(buttonClimberRelease))
		{
			grabber.armRelease();
			grabber.handRelease();
		}
		//Manipulator
		if(perifController.GetRawButton(buttonGrabHatch))
		{
			manipulator.grabHatch(.5);
		}
		if(perifController.GetRawButton(buttonReleaseHatch))
		{
			manipulator.hatchKickerExtend();
		}
	}


}

void Robot::UpdatePreferences()
{
	prefs = Preferences::GetInstance();

	driveBase.SetTrim(prefs->GetDouble("LeftForwardTrim", 0.82),
					  prefs->GetDouble("RightForwardTrim", 1.0),
					  prefs->GetDouble("LeftReverseTrim", 1.0),
					  prefs->GetDouble("RightReverseTrim", 1.0));

	speedNormal = prefs->GetFloat("SpeedNormal", 0.6f);
	speedTurtle = prefs->GetFloat("SpeedTurtle", 0.35f);
	speedBoost = prefs->GetFloat("SpeedBoost", 1.0f);
	boostDecelerationTime = prefs->GetFloat("BoostDecelTime", 0.5f);
	// Get specified delay for autonomous
	frc::SmartDashboard::SetDefaultNumber("Auto Delay", 0);
	autoDelay = frc::SmartDashboard::GetNumber("Auto Delay", 0);


	// Setup autonomous strategy chooser
	autoStrategyChooser.AddDefault("Nothing", &AUTO_STRATEGIES::NOTHING_OPTIONS);
	autoStrategyChooser.AddObject("Spin", &AUTO_STRATEGIES::SPIN_OPTIONS);
	//autoStrategyChooser.AddObject("R Inner Switch", &AUTO_STRATEGIES::RIGHT_SWITCH_INNER_OPTIONS);
	//autoStrategyChooser.AddObject("L Inner Switch", &AUTO_STRATEGIES::LEFT_SWITCH_INNER_OPTIONS);
	frc::SmartDashboard::PutData("Autonomous Strategies", &autoStrategyChooser);

	// Determine switch setup to select strategy.


}
// Returns true if at target


START_ROBOT_CLASS(Robot)
