#include "Climber.h"

Climber::Climber(int leftClimberUpPort, int leftClimberDownPort, int rightClimberUpPort, int rightClimberDownPort, int winchMotorPort) :
	leftClimber(leftClimberUpPort, leftClimberDownPort), rightClimber(rightClimberUpPort, rightClimberDownPort), winch(winchMotorPort)

{
	leftClimber.Set(frc::DoubleSolenoid::Value::kOff);
	rightClimber.Set(frc::DoubleSolenoid::Value::kOff);
}

void Climber::StopCompressor(){
	hindsightCompressor.Stop();
}

void Climber::LiftClimber() {

}