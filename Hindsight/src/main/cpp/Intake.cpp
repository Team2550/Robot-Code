#include "Intake.h"

Intake::Intake (int intakeMotorPort):
	intakeMotor(intakeMotorPort)
{
	intakeMotor.SetInverted(false);
}

void Intake::Start (){
	intakeMotor.Set(1);
}

void Intake::Stop (){
	intakeMotor.Set(0);
}