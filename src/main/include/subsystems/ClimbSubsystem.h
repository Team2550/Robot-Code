#pragma once

#include "Constants.h"
#include <frc/DigitalInput.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <cmath>

class ClimbSubsystem : public frc2::SubsystemBase {
public:
	ClimbSubsystem();

	/**
	 * @brief Returns the value of the Limit Switch.
	 */
	bool GetSwitchValue();

	/**
	 * @brief Raises the climber so that it may climb.
	 *
	 * @param[in] upSpeed speed to move the climber up.
	 * @param[in] downSpeed speed to move the climber down.
	 */
	void Climb(double upSpeed, double downSpeed);

	/**
	 * @brief Stops the motor for the Climb Subsystem.
	 */
	void Stop();

private:
	// Motor Controllers
	frc::VictorSP m_climbMotor;
	frc::DigitalInput m_climbSwitch;
};