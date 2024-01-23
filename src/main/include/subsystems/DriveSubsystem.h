#pragma once

#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/Watchdog.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/dimensionless.h>

#include "Constants.h"

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
	 *
	 */
	void ArcadeDrive(double speed, double rotation);

	/**
	 * @brief Drives the robot using tank controls.
	 *
	 * Also known as west-coast or differential, intended
	 * so that two sticks drive seperate sets of wheels.
	 *
	 * @param[in] leftSpeed The speed to run the left-side motors.
	 * @param[in] rightSpeed The speed to run the right-side motors.
	 *
	 */
	void TankDrive(double leftSpeed, double rightSpeed);

	/**
	 * @brief Resets the drive encoders to read zero.
	 */
	void ResetEncoders();

	/**
	 * @brief Gets the left drive encoder.
	 */
	frc::Encoder& GetLeftEncoder();

	/**
	 * @brief Gets the right drive encoder.
	 */
	frc::Encoder& GetRightEncoder();

	/**
	 * @brief Gets the average encoder distance between 2 encoders.
	 *
	 * @return the average of the 2 encoder readings.
	 */
	double GetAverageEncoderDistance();

private:
	// Motor Controllers
	frc::VictorSP m_frontLeft;
	frc::VictorSP m_rearLeft;
	frc::Encoder m_leftEncoder;
	frc::MotorControllerGroup m_left { m_frontLeft, m_rearLeft };
	frc::SlewRateLimiter<units::scalar> frontLeftFilter { 0.5 / 1_s };
	frc::SlewRateLimiter<units::scalar> rearLeftFilter { 0.5 / 1_s };

	frc::VictorSP m_frontRight;
	frc::VictorSP m_rearRight;
	frc::Encoder m_rightEncoder;
	frc::MotorControllerGroup m_right { m_frontRight, m_rearRight };
	frc::SlewRateLimiter<units::scalar> frontRightFilter { 0.5 / 1_s };
	frc::SlewRateLimiter<units::scalar> rearRightFilter { 0.5 / 1_s };

	// Drive Controller
	frc::MecanumDrive m_drive { m_frontLeft, m_rearLeft, m_frontRight, m_rearRight };
};
