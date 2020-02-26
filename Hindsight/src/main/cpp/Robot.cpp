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
				 driveBase(0, 1, 0, 1, 2, 3, 6.07 * M_PI, 2048) 
				 // Pulses per rotation is set by encoder DIP switch. 2048 PPR uses DIP switch configuration 0000.
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
	trimTest.Reset();
	trimTest.Start();
}

void Robot::AutonomousPeriodic() {
	// TODO: Auto
	if (trimTest.Get() <= 10.0){
		driveBase.Drive(0.5,0.5);
	} else {
		driveBase.Stop();
	}
}

void Robot::TeleopInit() {
	// TODO: TeleopInit
}

void Robot::TeleopPeriodic() {

	// Input changes will happen here
	udpReceiver.getTeleopUDPData();

	//std::cout << "Left: " << std::setw(5) << driveBase.GetLeftDistance() << ' '
	//          << "Right: " << std::setw(5) << driveBase.GetRightDistance() << ' '
	//		  << "Angle: " << std::setw(5) << gyroscope.GetAngle() << std::endl; 


	float leftSpeed = Utility::Deadzone(-inputController.leftTankAxis());
	float rightSpeed = Utility::Deadzone(-inputController.rightTankAxis());
	float baseSpeed = speedNormal;

	std::cout << "Left Joystick: " << inputController.leftTankAxis() << " Right Joystick: " << inputController.rightTankAxis() << std::endl;

	if (inputController.climb()){
		std::cout << "this will do things soon" << std::endl;
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

	driveBase.SetTrim(//prefs -> GetDouble("LeftForwardTrim", 0.88),
					  prefs -> GetDouble("RightForwardTrim", 1.0),
					  //prefs -> GetDouble("LeftReverseTrim", 0.88),
					  prefs -> GetDouble("RightReverseTrim", 1.0),
					  prefs -> GetDouble("LeftReverseTrim", 1.0),
					  prefs -> GetDouble("LeftForwardTrim", 0.88)
					  );

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
