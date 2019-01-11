//This code was made for the FRC 2019 season
//By: Brayton Kerekffy and Travis Albers
#include "Robot.h"

// driver: (int) xBox controller number
// driveBase:  (float) max power, (float) max boost power, (int) left motor port,
//             (int) right motor port
Robot::Robot() : driveController(0), perifController(1),
				 autoController(&driveBase, &gyroscope),
				 gyroscope(frc::SPI::Port::kOnboardCS0),
				 driveBase(0, 1, 0, 1, 2, 3, 6.07 * M_PI, 512) // Pulses per rotation is set by encoder DIP switch. 512 PPR uses DIP switch configuration 0001.
{
	axisTankLeft = xbox::axis::leftY;
	axisTankRight = xbox::axis::rightY;
	buttonBoost = xbox::btn::rb;
	buttonTurtle = xbox::btn::lb;


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
	std::cout << "Gyro calibrated" << std::endl;

	// Start Video Stream
	CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::AutonomousInit()
{
	UpdatePreferences();

	driveBase.Stop();

	timer.Reset();
	timer.Start();

}

void Robot::AutonomousPeriodic()
{

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
	std::cout << "Left: " << std::setw(5) << driveBase.GetLeftDistance() << ' '
	          << "Right: " << std::setw(5) << driveBase.GetRightDistance() << ' '
			  << "Angle: " << std::setw(5) << gyroscope.GetAngle() << std::endl;

	// Drivebase
	// Use D-pad of controller to drive in basic directions
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

}


void Robot::UpdatePreferences()
{
	prefs = Preferences::GetInstance();

	driveBase.SetTrim(prefs->GetDouble("LeftForwardTrim", 1.0),
					  prefs->GetDouble("RightForwardTrim", 1.0),
					  prefs->GetDouble("LeftReverseTrim", 1.0),
					  prefs->GetDouble("RightReverseTrim", 1.0));

	speedNormal = prefs->GetFloat("SpeedNormal", 0.5f);
	speedTurtle = prefs->GetFloat("SpeedTurtle", 0.25f);
	speedBoost = prefs->GetFloat("SpeedBoost", 1.0f);
	boostDecelerationTime = prefs->GetFloat("BoostDecelTime", 0.5f);
	// Get specified delay for autonomous
	frc::SmartDashboard::SetDefaultNumber("Auto Delay", 0);
	autoDelay = frc::SmartDashboard::GetNumber("Auto Delay", 0);

	// Setup autonomous strategy chooser
	//autoStrategyChooser.AddObject("R Exchange", &AUTO_STRATEGIES::RIGHT_EXCHANGE_OPTIONS);
	//autoStrategyChooser.AddObject("L Exchange", &AUTO_STRATEGIES::LEFT_EXCHANGE_OPTIONS);
	//autoStrategyChooser.AddObject("R Inner Switch", &AUTO_STRATEGIES::RIGHT_SWITCH_INNER_OPTIONS);
	//autoStrategyChooser.AddObject("L Inner Switch", &AUTO_STRATEGIES::LEFT_SWITCH_INNER_OPTIONS);
	//frc::SmartDashboard::PutData("Autonomous Strategies", &autoStrategyChooser);

	// Determine switch setup to select strategy.


}
START_ROBOT_CLASS(Robot)
