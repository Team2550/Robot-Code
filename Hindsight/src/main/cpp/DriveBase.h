#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include "Utility.h"
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/controller/PIDController.h>
#include <frc/motorcontrol/Spark.h>
#include <iomanip>
#include <iostream>
#include <math.h>

const double K_P = 1;
const double K_I = 1;
const double K_D = 1;

class DriveBase {
  public:
	DriveBase(int leftMotorPort, int rightMotorPort, int leftEncoderPortA,
			  int leftEncoderPortB, int rightEncoderPortA,
			  int rightEncoderPortB, double wheelCircumference,
			  int encoderPulsesPerRotation);

	double GetLeftSpeed();
	double GetRightSpeed();
	void Drive(double leftSpeed, double rightSpeed);
	void Drive(double speed);
	void Stop();
	bool IsStopped();
	void ResetDistance();
	double GetLeftDistance();
	double GetRightDistance();
	void SetTrim(float leftForwardTrim, float rightForwardTrim,
				 float leftReverseTrim, float rightReverseTrim);
	// float DriveBase(PowerDistribution& pdp);
	float GetAmps(PowerDistribution &pdp);
	void SetReversed(bool reverse);
	bool GetReversed();

  private:
	Spark leftMotor;
	Spark rightMotor;

	Encoder leftEncoder;
	Encoder rightEncoder;

	frc2::PIDController leftController;	 //(double K_P, double K_I, double K_D);
	frc2::PIDController rightController; //(double K_P, double K_I, double K_D);

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
};

#endif
