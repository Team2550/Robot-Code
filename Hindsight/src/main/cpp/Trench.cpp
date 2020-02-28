#include "Trench.h"

Trench::Trench(int trenchMotorPort) :
	trenchMotor(trenchMotorPort)
{}

void Trench::SpinTrench(double speed){
	trenchMotor.Set(speed);
}