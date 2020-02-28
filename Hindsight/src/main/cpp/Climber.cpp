#include "Climber.h"

Climber::Climber(int leftClimberUpPort, int leftClimberDownPort, int rightClimberUpPort, int rightClimberDownPort, int winchMotorPort) :
	leftClimber(leftClimberUpPort, leftClimberDownPort), rightClimber(rightClimberUpPort, rightClimberDownPort), winch(winchMotorPort)

{
	leftClimber.Set(frc::DoubleSolenoid::kReverse);
	rightClimber.Set(frc::DoubleSolenoid::kReverse);
}

void Climber::StartCompressor(){
	hindsightCompressor.Start();
}

void Climber::StopCompressor(){
	hindsightCompressor.Stop();
}

void Climber::WinchSpeed(double speed){
	winch.Set(speed);
}

void Climber::LiftClimber() {
	leftClimber.Set(frc::DoubleSolenoid::kForward);
	rightClimber.Set(frc::DoubleSolenoid::kForward);
}

void Climber::LowerClimber() {
	leftClimber.Set(frc::DoubleSolenoid::kReverse);
	rightClimber.Set(frc::DoubleSolenoid::kReverse);
}