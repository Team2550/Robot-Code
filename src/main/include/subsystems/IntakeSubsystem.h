#pragma once

#include "Constants.h"
#include <cmath>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <frc/DigitalOutput.h>
#include <frc/MotorSafety.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/voltage.h>

class IntakeSubsystem : public frc2::SubsystemBase {
public:
	IntakeSubsystem();

	/**
	 * @brief Spins the motor to intake the ring.
	 */
	void IntakeRing();

	/**
	 * @brief Spins the motor to expell the ring from intake.
	 */
	void ExpellRing();

	/**
	 * @brief Spins the flywheels for the launch mechanism
	 * 		  at 12% speed for low goal
	 */
	void GentleRing();

	/**
	 * @brief Stops the motors for the Intake Subsystem.
	 */
	void StopIntake();

	/**
	 * @todo Implement calculation for cancling out both triggers.
	 * @brief Pivots the Intake.
	 *
	 * @param[in] upSpeed Speed to pivot the intake upwards.
	 * @param[in] downSpeed Speed to pivot the intake downwards.
	 */
	void PivotIntake(double upSpeed, double downSpeed);

private:
	// Motor Controllers
	ctre::phoenix::motorcontrol::can::TalonSRX m_intakePivot;
	frc::VictorSP m_intakeMotor;
};