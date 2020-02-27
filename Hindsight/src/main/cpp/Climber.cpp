#include "Climber.h"

Climber::Climber(int leftClimberUpPort, int leftClimberDownPort, int rightClimberUpPort, int rightClimberDownPort, int winchMotorPort) :
	leftClimber(leftClimberUpPort, leftClimberDownPort), rightClimber(rightClimberUpPort, rightClimberDownPort), winch(winchMotorPort)

{
	leftClimber.Set(frc::DoubleSolenoid::Value::kOff);
	rightClimber.Set(frc::DoubleSolenoid::Value::kOff);
	hindsightCompressor.SetClosedLoopControl(false);
}

void Climber::StartCompressor(){
	hindsightCompressor.Start();
}

void Climber::StopCompressor(){
	hindsightCompressor.Stop();
}

void Climber::WinchClockwise(){
	winch.Set(-1);
}

void Climber::WinchCounterclockwise(){
	winch.Set(1);
}

void Climber::WinchStop(){
	winch.Set(0);
}

void Climber::LiftClimber() {
	leftClimber.Set(frc::DoubleSolenoid::Value::kForward);
	rightClimber.Set(frc::DoubleSolenoid::Value::kForward);
}