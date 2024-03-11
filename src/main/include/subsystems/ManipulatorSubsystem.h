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
	 * @brief Moves the manipulator.
	 * 		  The down value is subtracted from the up value.
	 * 		  This allows for the values to cancel out.
	 *
	 * @param[in] upValue The speed of which to move up.
	 * @param[in] downValue The speed of which to move down.
	 */
	void MoveArm(double upValue, double downValue);

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