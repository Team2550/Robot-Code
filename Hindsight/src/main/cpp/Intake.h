#ifndef INTAKE_H
#define INTAKE_H

#include <frc/Spark.h>
#include <frc/Encoder.h>
#include <frc/PowerDistributionPanel.h>
#include <math.h>
#include "Utility.h"

class Intake{
public:
	Intake(int intakeMotorPort);
	void Start();
	void Stop();
	bool IsActive();
private:
	frc::Spark intakeMotor;
	bool isActive;
};

#endif