#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include "Utility.h"
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/controller/PIDController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/drive/MecanumDrive.h>

#include <iomanip>
#include <iostream>
#include <math.h>


class DriveBase {
  public:
	DriveBase::DriveBase(int leftFrontPort, int rightFrontPort,
					 int leftRearPort, int rightRearPort);

  private:
	Spark leftFrontMotor;
	VictorSP leftRearMotor;
	VictorSP rightFrontMotor;
	Spark rightRearMotor;

	int leftFrontMotorValue;
	int leftRearMotorValue;
	int rightFrontMotorValue;
	int rightRearMotorValue;
};

#endif
