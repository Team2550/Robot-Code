#pragma once

#include <frc/Compressor.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc/PowerDistribution.h>
#include <frc/motorcontrol/Spark.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

class ManipulatorSubsystem : public frc2::SubsystemBase {
public:
	ManipulatorSubsystem();

	/***
	 * @brief Moves the manipulator
	 *
	 * @param value The speed of which to move.
	 */
	void MoveArm(double value);

	/***
	 * @brief Actuates the hand
	 */
	void ArmGrab();

	/***
	 * @brief Deactuates the hand
	 */
	void ArmRelease();

	/***
	 * @brief the hand
	 */
	void ArmRest();

	/**
	 * @brief Drives the manipulator's winch.
	 * @param speed The speed to drive the winch (-1 to 1)
	 */
	void DriveWinch(double speed);

private:
	// Motor Controllers
	frc::Spark m_manipulator;
	frc::Spark m_manipulatorWinch;
	frc::DigitalInput m_manipulatorLimit;

	// Pneumatics
	frc::DoubleSolenoid m_manipulatorSolenoid { frc::PneumaticsModuleType::CTREPCM, 0, 1 };
};