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

Robot::Robot() : inputController(),
				 udpReceiver(),
				 gyroscope(frc::SPI::Port::kOnboardCS0),
				 intake(2),
				 climber(0, 1, 2, 3, 3),
				 trench(4),
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


	// Sets LimeLight to off by default
	limelight->PutNumber("ledMode", 1);
}

void Robot::AutonomousInit() {
	autoDelayTimer.Reset();
	autoTimer.Reset();
	autoDelayTimer.Start();
	autoTimer.Start();
}

void Robot::AutonomousPeriodic() {
	if (autoTimer.Get() <= 1.0){
		driveBase.Drive(0.42,0.42);
	} else {
		driveBase.Stop();
	}
	
	/*if(autoDelayTimer.Get() >= autoDelay 0){
		if(autoTimer.Get() <= 2autoLength + autoDelay){
			driveBase.Drive(0.42,0.42);
		} else {
			driveBase.Stop();
		}
	}*/
}

void Robot::TeleopInit() {
	
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

	if (inputController.climb()){
		if (climbGrabToggleCount % 2 == 0){
			climber.LiftClimber();
		} else {
			climber.LowerClimber();
		}
		std::cout << "Climb Button Pressed" << std::endl; 
		climbGrabToggleCount++;
	}

	trench.SpinTrench(inputController.trenchSpeedAxis());

	climber.WinchSpeed(inputController.winchSpeed());

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
					  prefs -> GetDouble("LeftReverseTrim", 0.88),
					  prefs -> GetDouble("LeftForwardTrim", 0.88)
					  );

	speedNormal = prefs -> GetFloat("SpeedNormal", 0.6f);
	speedTurtle = prefs -> GetFloat("SpeedTurtle", 0.35f);
	speedBoost = prefs -> GetFloat("SpeedBoost", 1.0f);
	boostDecelerationTime = prefs -> GetFloat("BoostDecelTime", 0.5f);
	// Get specified delay for autonomous
	frc::SmartDashboard::SetDefaultNumber("Auto Delay", 0);
	frc::SmartDashboard::SetDefaultNumber("Auto Length", 0);
	autoDelay = frc::SmartDashboard::GetNumber("Auto Delay", 0);
	autoLength = frc::SmartDashboard::GetNumber("Auto Length", 1);

}

int main() {
	return frc::StartRobot<Robot>();
}
