#pragma once

#include "Constants.h"
#include <frc/DigitalOutput.h>
#include <frc/MotorSafety.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <units/voltage.h>

#include <cmath>

class LaunchSubsystem : public frc2::SubsystemBase {
public:
	LaunchSubsystem();

	/**
	 * @brief Spins the wheels for the launch mechanism
	 */
	void LaunchRing();

	/**
	 * @brief Spins the lower wheel for the launch mechanism.
	 * Sends the ring for launch.
	 */
	void PushRing();

	/**
	 * @brief Runs the wheels in reverse to store the ring.
	 */
	void IntakeRing();

	/**
	 * @brief Stops the motors for the Launch Subsystem.
	 */
	void Stop();

	/**
	 * @brief Sets the state of the DIO pin for the red light.
	 *
	 * @param[in] bool If true light is on, else light is off.
	 */
	void RedLight(bool State);

	/**
	 * @brief Sets the state of the DIO pin for the blue light.
	 *
	 * @param[in] bool If true light is on, else light is off.
	 */
	void BlueLight(bool State);

private:
	// Motor Controllers
	rev::CANSparkMax m_launchMotor;
	rev::CANSparkMax m_pushMotor;

	frc::DigitalOutput m_redLight;
	frc::DigitalOutput m_blueLight;
};