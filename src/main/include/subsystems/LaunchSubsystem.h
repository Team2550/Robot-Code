#pragma once

#include "Constants.h"
#include <frc/MotorSafety.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/voltage.h>

#include <cmath>

class LaunchSubsystem : public frc2::SubsystemBase {
public:
	LaunchSubsystem();

	/**
	 * @brief Spins the wheels for the launch mechanism
	 */
	void LaunchRing();

	void PushRing();

	void IntakeRing();

	void Stop();

private:
	// Motor Controllers
	frc::PWMSparkMax m_launchMotor;
	frc::PWMSparkMax m_pushMotor;
};