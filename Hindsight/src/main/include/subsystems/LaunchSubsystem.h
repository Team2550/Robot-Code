#pragma once

#include <frc/PowerDistribution.h>
#include <frc/motorcontrol/Spark.h>
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

	/**
	 * @brief Moves the ring in for launch
	 */
	void PushRing();

private:
	// Motor Controllers
	frc::Spark m_launchMotor;
	frc::Spart m_pushMotor;
};