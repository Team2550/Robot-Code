#include "Shooter.h"

Shooter::Shooter (int shooterMotorPort):
    shooterMotor(shooterMotorPort)
{
    shooterMotor.SetInverted(true);
}

void Shooter::Start(){
    Shooter::SetSpeed(shooterSpeed);
}

void Shooter::Stop(){
    shooterMotor.Set(0);
}

bool Shooter::IsActive(){
    if(shooterMotor.Get() == 0){
        return false;
    } else {
        return true;
    }
}

void Shooter::SetSpeed(double speed){
    shooterSpeed = speed;
    shooterMotor.Set(shooterSpeed);
}
