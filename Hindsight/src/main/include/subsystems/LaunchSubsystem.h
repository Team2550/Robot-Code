#pragma once

#include <frc/MotorSafety.h>
#include <frc/PowerDistribution.h>
#include <frc/motorcontrol/VictorSP.h> 
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

#include <cmath>

class LaunchSubsystem : public frc2::SubsystemBase {
public:
	LaunchSubsystem();

	/**
	 * @brief Spins the wheels for the launch mechanism
	 */
	void LaunchRing();

	void IntakeRing();

private:
	// Motor Controllers
	frc::VictorSP m_launchMotor;
	frc::VictorSP m_pushMotor;
};
