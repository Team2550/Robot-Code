#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <cmath>

#include "subsystems/DriveSubsystem.h"

// Balances the robot on the Charge Station
class DriveBalance : public frc2::CommandHelper<frc2::CommandBase, DriveBalance> {
public:
	explicit DriveBalance(double speed, DriveSubsystem* susbsystem);

	void Initialize() override;

	void Execute() override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;

	double error;
	double currentAngle;
	double m_speed;
	int m_status = 0;
};