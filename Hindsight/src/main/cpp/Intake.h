#ifndef INTAKE_H
#define INTAKE_H

#include <frc/motorcontrol/Spark.h>
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <math.h>
#include "Utility.h"

class Intake{
public:
	Intake(int intakeMotorPort);
	void Start();
	void Stop();
	bool IsActive();
private:
	Spark intakeMotor;
	bool isActive;
};

#endif