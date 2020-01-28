#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include <frc/Spark.h>
#include <frc/Encoder.h>
#include <frc/PowerDistributionPanel.h>
#include <math.h>
#include "Utility.h"
#include <iostream>
#include <iomanip>

class DriveBase
{
public:
	DriveBase(int leftMotorPort, int rightMotorPort,
			  int leftEncoderPortA, int leftEncoderPortB,
			  int rightEncoderPortA, int rightEncoderPortB,
			  double wheelCircumference, int encoderPulsesPerRotation);

	double GetLeftSpeed();
	double GetRightSpeed();
	void Drive(double leftSpeed, double rightSpeed);
	void Drive(double speed);
	void Stop();
	bool IsStopped();
	void ResetDistance();
	double GetLeftDistance();
	double GetRightDistance();
	void SetTrim(float leftForwardTrim, float rightForwardTrim, float leftReverseTrim, float rightReverseTrim);
	//float DriveBase(PowerDistributionPanel& pdp);
	float GetAmps(PowerDistributionPanel& pdp);
	void SetReversed(bool reverse);
	bool GetReversed();

private:
	Spark leftMotor;
	Spark rightMotor;

	Encoder leftEncoder;
	Encoder rightEncoder;

	float leftForwardTrim;
	float rightForwardTrim;
	float leftReverseTrim;
	float rightReverseTrim;


	int rightMotorPortValue;
	int leftMotorPortValue;
	int leftEncoderPortAValue;
	int leftEncoderPortBValue;
	int rightEncoderPortAValue;
	int rightEncoderPortBValue;
	double wheelCircumferenceValue;
	int encoderPulsesPerRotationValue;

	bool isReversed;

	//double lastRightEncoderValue;
	//double lastLeftEncoderValue;
	double lastRightSpeedValue;
	double lastLeftSpeedValue;
};

#endif
