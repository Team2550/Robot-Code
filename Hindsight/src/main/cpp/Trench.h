#ifndef TRENCH_H
#define TRENCH_H

#include <frc/Spark.h>

class Trench {
public:
	Trench(int trenchMotorPort);
	void SpinTrench(double speed);
private:
	frc::Spark trenchMotor;
};

#endif