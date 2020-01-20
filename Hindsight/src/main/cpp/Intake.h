#ifndef INTAKE_H
#define INTAKE_H

#include <frc/Victor.h>
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
	Victor intakeMotor;
	bool isActive;
};

#endif