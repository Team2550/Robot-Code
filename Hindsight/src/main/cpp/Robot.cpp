//This code was made for the FRC 2019 season
//By: Brayton Kerekffy and Travis Albers
#include "Robot.h"

// driver: (int) xBox controller number
// driveBase:  (float) max power, (float) max boost power, (int) left motor port,
//             (int) right motor port

Robot::Robot() : inputController(),
				 udpReceiver(),
				 gyroscope(frc::SPI::Port::kOnboardCS0),
				 // 0 for right, 1 for left on El Churro
				 driveBase(1, 0, 0, 1, 2, 3, 6.07 * M_PI, 512) // Pulses per rotation is set by encoder DIP switch. 512 PPR uses DIP switch configuration 0001.
{
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

	driveBase.setReversed(true);

	// Start Video Stream
	// URL is "http://10.25.50.94:8080/"
	CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::AutonomousInit()
{
	std::cout << "This does NOTHING!";
}

void Robot::AutonomousPeriodic()
{
	std::cout << "This does NOTHING!";
}

void Robot::TeleopInit(){
	std::cout << "This does NOTHING!";
}

void Robot::TeleopPeriodic()
{
	udpReceiver.getTeleopUDPData();

	std::cout << "Left: " << std::setw(5) << driveBase.GetLeftDistance() << ' '
	          << "Right: " << std::setw(5) << driveBase.GetRightDistance() << ' '
			  << "Angle: " << std::setw(5) << gyroscope.GetAngle() << std::endl;


	float leftSpeed = Utility::Deadzone(-inputController.leftTankAxis());
	float rightSpeed = Utility::Deadzone(-inputController.rightTankAxis());

	float baseSpeed = speedNormal;

	if (inputController.turtle()){ 
		baseSpeed = speedTurtle;
	} else if (inputController.boost()){
		baseSpeed = speedBoost;
		boostPressTime = timer.Get();
	} else if (timer.Get() < boostPressTime + boostDecelerationTime) {
		baseSpeed = speedBoost + (speedNormal - speedBoost) * ((timer.Get() - boostPressTime) / boostDecelerationTime);
	}
	driveBase.Drive(leftSpeed * baseSpeed,
					rightSpeed * baseSpeed);
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


}
// Returns true if at target

//Old way, was creating a complier warning
//START_ROBOT_CLASS(Robot)

//New way (maybe), suggested by the complier
int main() {
	return frc::StartRobot<Robot>();
}