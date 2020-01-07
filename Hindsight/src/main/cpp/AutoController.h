#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include <frc/WPILib.h>
#include <iostream>
#include "DriveBase.h"

class Robot;

class AutoController
{
public:
	// WAIT_UNTIL:		Pauses execution until 'target' seconds has passed since the start of the round. (Drives if speeds are given)
	// WAIT_TIME:		Pauses execution for 'target' seconds. (Drives if speeds are given)
	// DRIVE_TO:		Drives the robot at the speed given to a distance 'target' inches from the last time the distance was reset. (Distance is reset at start)
	// DRIVE_DIST:		Drives the robot at the speed for 'target' inches.
	// ROTATE_TO:		Rotates the robot to 'target' degrees relative to the starting position.
	// ROTATE_DEG:  	Rotates the robot 'target' degrees relative to its current position.
	//            		Left and right motor speeds dictate how the robot rotates. If only one speed is given, robot rotates in place.
	// RESET_DIST_0:	Resets the measured distances to 0.
	// EXTEND:			Begins extending the bulldozer.
	// RETRACT:			Begins retracting the bulldozer.
	// KICK:			Activates the kicker piston on top of the bulldozer.
	// 		Note: DRIVE_TO, DRIVE_DIST, ROTATE_TO, and ROTATE_DEG slow down on approach to target if 'stopAtTarget' is true.
	enum InstructionType { WAIT_UNTIL, WAIT_TIME, DRIVE_TO, DRIVE_DIST, ROTATE_TO, ROTATE_DEG, RESET_DIST_0, DRIVE_UNTIL, EXTEND, RETRACT, KICK }; //, RESET_DIST_ULTRA  };

	struct Instruction
	{
		InstructionType type;
		double target = 0; // Distance or angle, depending on instruction
		bool stopAtTarget = true; // Slow down/stop near target.
		double leftSpeed = 0; // Acts as speed of both sides if only one specified.
		double rightSpeed = leftSpeed; // Defaults to both sides sharing the same speed
	};

	struct InstructionSet
	{
		const Instruction* steps;
		unsigned int count;
	};

	/**struct PositionOptions
	{
		const InstructionSet* leftOption;
		const InstructionSet* rightOption;
	};**/

	AutoController(Robot* robot);
	~AutoController();

	// Name:	Execute
	// Parameters:
	//		driveBase (I/O)	- The drivebase of the robot. Used to read encoders and set motor speeds.
	//		gyroscope (I)	- The gyroscope on the robot. Used to detect robot's rotation.
	//		autoTimer (I)	- Timer that measures how much time has passed since the match started. Used for timing.
	// Return:
	//		True if strategy is complete.
	void Init(const InstructionSet instructionSet);
	bool Execute();

private:
	Robot* robot;
	Timer timer;

	InstructionSet instructionSet;

	unsigned int currentInstruction;
	double instructionStartTime;
	double instructionStartDistance;
	double instructionStartAngle;
	double instructionTargetAngle;
	bool bulldozerKicking;
	bool doAmpTest = false;

	bool AutoDriveToDist( double leftSpeed, double rightSpeed, double targetDistance, double targetAngle, bool stopAtTarget );
	bool AutoRotateToAngle( double leftSpeed, double rightSpeed, double targetAngle, bool stopAtTarget );
	double GetCurrentDistance();

};

#endif
