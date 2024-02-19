#pragma once

#include "Constants.h"
#include <frc/ADXRS450_Gyro.h>
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <cmath>

class DriveSubsystem : public frc2::SubsystemBase {
public:
	DriveSubsystem();

	/**
	 * @brief Drives the robot using arcade controls.
	 *
	 * Intended so that one stick controls robot speed
	 * while the other controls rotation.
	 *
	 * @param[in] speed The speed to drive the robot.
	 * @param[in] rotation The rotation to steer the robot to.
	 * @param[in] squareInputs Decreases input sensityivity at low speeds.
	 *
	 */
	void ArcadeDrive(double speed, double rotation, bool squareInputs);

	/**
	 * @brief Drives the robot using tank controls.
	 *
	 * Also known as west-coast or differential, intended
	 * so that two sticks drive seperate sets of wheels.
	 *
	 * @param[in] leftSpeed The speed to run the left-side motors.
	 * @param[in] rightSpeed The speed to run the right-side motors.
	 * @param[in] squareInputs Decreases input sensityivity at low speeds.
	 *
	 */
	void TankDrive(double leftSpeed, double rightSpeed, bool squareInputs);

	/**
	 * @brief Resets the double returned by the gyro to 0.
	 */
	void ResetAngle();

	/**
	 * @brief Returns the current heading of the gyro from 360 -> 361
	 *
	 * @param[out] angle double, current angle from the gyro.
	 */
	double GetCurrentAngle();

private:
	// Motor Controllers
	frc::VictorSP m_frontLeft;
	frc::VictorSP m_rearLeft;
	frc::MotorControllerGroup m_left { m_frontLeft, m_rearLeft };

	frc::VictorSP m_frontRight;
	frc::VictorSP m_rearRight;
	frc::MotorControllerGroup m_right { m_frontRight, m_rearRight };

	// Gyro
	frc::ADXRS450_Gyro m_gyro;

	// Drive Controller
	frc::MecanumDrive m_drive { m_frontLeft, m_rearLeft, m_frontRight, m_rearRight };
};
