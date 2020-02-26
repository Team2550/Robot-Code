// 
//	© 2020 Skynet 2550
//
//	Programming Lead: Charlie Welsh
//
//	Programming Team: Charlie Welsh
//
//	Programming Mentors: Lance Booth, Alex Pearson
//
#include "Robot.h"

// driveBase:  (float) max power, (float) max boost power, (int) left motor port,
//             (int) right motor port


// These are for the intake toggle later.
bool intakeToggleOn = false;
bool intakeTogglePressed = false;

Robot::Robot() : inputController(),
				 udpReceiver(),
				 gyroscope(frc::SPI::Port::kOnboardCS0),
				 intake(2),
				 // 0 for right, 1 for left on El Churro
				 driveBase(1, 0, 0, 1, 2, 3, 6.07 * M_PI, 512) 
				 // Pulses per rotation is set by encoder DIP switch. 512 PPR uses DIP switch configuration 0001.
{
	boostPressTime = -999;
	UpdatePreferences();
}

Robot::~Robot() {

}

void Robot::RobotInit() {
	gyroscope.Calibrate();

	driveBase.SetReversed(true);

	// Start Video Stream
	// URL is "http://10.25.50.94:8080/"
	CameraServer::GetInstance() -> StartAutomaticCapture();
}

void Robot::AutonomousInit() {
	// TODO: Auto
}

void Robot::AutonomousPeriodic() {
	// TODO: Auto
}

void Robot::TeleopInit() {
	// TODO: TeleopInit
}

void Robot::TeleopPeriodic() {

	// Input changes will happen here
	udpReceiver.getTeleopUDPData();

	std::cout << "Left: " << std::setw(5) << driveBase.GetLeftDistance() << ' '
	          << "Right: " << std::setw(5) << driveBase.GetRightDistance() << ' '
			  << "Angle: " << std::setw(5) << gyroscope.GetAngle() << std::endl; 


	float leftSpeed = Utility::Deadzone(-inputController.leftTankAxis());
	float rightSpeed = Utility::Deadzone(-inputController.rightTankAxis());
	float baseSpeed = speedNormal;


	if (inputController.intake()) { 
		if (intake.IsActive()) {
			intake.Stop();
		} else {
			intake.Start();
		}
	} 

	
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
	if(gameData.length() > 0)
	{
		// If there's time, make this an automated process with a color sensor or vision; utilizing the switch. For now, it's just for this.
		switch (gameData[0]) {
			case 'B' :
				frc::SmartDashboard::PutString("WheelOfFortuneColor", gameData)
			break;
			case 'G' :
				frc::SmartDashboard::PutString("WheelOfFortuneColor", gameData)
			break;
			case 'R' :
				frc::SmartDashboard::PutString("WheelOfFortuneColor", gameData);
			break;
			case 'Y' :
				frc::SmartDashboard::PutString("WheelOfFortuneColor", gameData);
			break;
			default :
				frc::SmartDashboard::PutString("WheelOfFortuneColor", "No Color Yet");
			break;
		}
	} else {
	//Code for no data received yet
	}

	if (inputController.turtle()) { 
		baseSpeed = speedTurtle;
	} else if (inputController.boost()) {
		baseSpeed = speedBoost;
		boostPressTime = timer.Get();
	} else if (timer.Get() < boostPressTime + boostDecelerationTime) {
		baseSpeed = speedBoost + (speedNormal - speedBoost) * ((timer.Get() - boostPressTime) / boostDecelerationTime);
	}
	driveBase.Drive(leftSpeed * baseSpeed,
					rightSpeed * baseSpeed);
}

void Robot::UpdatePreferences() {

	prefs = Preferences::GetInstance();

	// Soon to be replaced

	driveBase.SetTrim(prefs -> GetDouble("LeftForwardTrim", 0.82),
					  prefs -> GetDouble("RightForwardTrim", 1.0),
					  prefs -> GetDouble("LeftReverseTrim", 1.0),
					  prefs -> GetDouble("RightReverseTrim", 1.0));

	speedNormal = prefs -> GetFloat("SpeedNormal", 0.6f);
	speedTurtle = prefs -> GetFloat("SpeedTurtle", 0.35f);
	speedBoost = prefs -> GetFloat("SpeedBoost", 1.0f);
	boostDecelerationTime = prefs -> GetFloat("BoostDecelTime", 0.5f);
	// Get specified delay for autonomous
	frc::SmartDashboard::SetDefaultNumber("Auto Delay", 0);
	autoDelay = frc::SmartDashboard::GetNumber("Auto Delay", 0);


}

int main() {
	return frc::StartRobot<Robot>();
}
