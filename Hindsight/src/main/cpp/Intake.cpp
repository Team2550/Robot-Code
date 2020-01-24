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

bool Intake::IsActive (){
	if(intakeMotor.Get() == 0){
		return false;
	} else {
		return true;
	} 
}