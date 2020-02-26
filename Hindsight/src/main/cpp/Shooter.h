#ifndef SHOOTER_H
#define SHOOTER_H

#include <frc/Spark.h>
#include <frc/PowerDistributionPanel.h>
#include <math.h>
#include "Utility.h"

class Shooter{
public:
    Shooter(int shooterMotorPort);
    void Start();
    void Stop();
    bool IsActive();
    void SetSpeed(double speed);
private:
    Spark shooterMotor;
    bool isActive;
    double shooterSpeed = 0.5;
};

#endif