//
//	© 2022 Skynet 2550
//
//	Programming Team: Garin Hamburg
//
#include "Robot.h"

//
// driveBase:  (int) Left Front port, (int) Right Front port, 
//             (int) Left Rear port, (int) Right Rear port
// 



// These are for the intake toggle later.
bool intakeToggleOn = false;
bool intakeTogglePressed = false;

Robot::Robot()
	: inputController(), udpReceiver(), gyroscope(frc::SPI::Port::kOnboardCS0), //Need gyro for DriveCartesian 
	  intake(2),
	  // 
	  driveBase(0, 1, 2, 3)
{
	boostPressTime = -999;
	UpdatePreferences();
}

Robot::~Robot() {}

void Robot::RobotInit() {
	gyroscope.Calibrate();


	// Start Video Stream
	// URL is "http://10.25.50.94:8080/"
	CameraServer::StartAutomaticCapture();
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
			  << "Right: " << std::setw(5) << driveBase.GetRightDistance()
			  << ' ' << "Angle: " << std::setw(5) << gyroscope.GetAngle()
			  << std::endl;

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

	if (inputController.turtle()) {
		baseSpeed = speedTurtle;
	} else if (inputController.boost()) {
		baseSpeed = speedBoost;
		boostPressTime = float(timer.Get());
	} else if (float(timer.Get()) < boostPressTime + boostDecelerationTime) {
		baseSpeed = speedBoost + (speedNormal - speedBoost) *
									 ((float(timer.Get()) - boostPressTime) /
									  boostDecelerationTime);
	}
	driveBase.Drive(leftSpeed * baseSpeed, rightSpeed * baseSpeed);
}

void Robot::UpdatePreferences() {

	// Soon to be replaced

	driveBase.SetTrim(Preferences::GetDouble("LeftForwardTrim", 0.82),
					  Preferences::GetDouble("RightForwardTrim", 1.0),
					  Preferences::GetDouble("LeftReverseTrim", 1.0),
					  Preferences::GetDouble("RightReverseTrim", 1.0));

	speedNormal = Preferences::GetFloat("SpeedNormal", 0.6f);
	speedTurtle = Preferences::GetFloat("SpeedTurtle", 0.35f);
	speedBoost = Preferences::GetFloat("SpeedBoost", 1.0f);
	boostDecelerationTime = Preferences::GetFloat("BoostDecelTime", 0.5f);
	// Get specified delay for autonomous
	frc::SmartDashboard::SetDefaultNumber("Auto Delay", 0);
	autoDelay = frc::SmartDashboard::GetNumber("Auto Delay", 0);
}

int main() { return frc::StartRobot<Robot>(); }
