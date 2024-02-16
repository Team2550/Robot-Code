#pragma once

#include "Constants.h"
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/DigitalInput.h>

#include <cmath>

class ClimbSubsystem : public frc2::SubsystemBase {
public:
	ClimbSubsystem();

    /**
     * @brief Raises the climber so that it may climb.
    */
    void Reach();

	/**
	 * @brief Retracts the climber so that it climbs.
	 */
	void Climb();

	/**
	 * @brief Stops the motor for the Climb Subsystem.
	 */
	void Stop();

private:
	// Motor Controllers
	frc::VictorSP m_climbMotor;
    frc::DigitalInput m_climbSwitch;
};