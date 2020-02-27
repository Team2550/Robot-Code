#ifndef CLIMBER_H
#define CLIMBER_H

#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include <frc/Spark.h>

class Climber {
public:
	Climber(int leftClimberUpPort, int leftClimberDownPort, int rightClimberUpPort, int rightClimberDownPort, int winchMotorPort);
	void StartCompressor();
	void StopCompressor();
	void LiftClimber();
	void WinchClockwise();
	void WinchCounterclockwise();
	void WinchStop();
private:
	frc::DoubleSolenoid leftClimber;
	frc::DoubleSolenoid rightClimber;
	frc::Compressor hindsightCompressor {0};
	frc::Spark winch;
};

#endif