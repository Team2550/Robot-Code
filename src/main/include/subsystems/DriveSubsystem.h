#pragma once

#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/VictorSP.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

#include <cmath>

class DriveSubsystem : public frc2::SubsystemBase
{
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
	 * @brief Drives mecanum wheels in arcade style
	 *
	 * Intended for use in 'arcade' style controls, where 1 stick controls movement
	 * and the other controls rotation.
	 *
	 * @param[in] speedV The speed in which the robot moves forward/backwards.
	 * @param[in] speedH The speed in which the robot moves left/right.
	 * @param[in] rotation The speed in which the direction the robot is facing is changed.
	 *
	 */
	void MecanumDrive(double speedV, double speedH, double rotation);

	/**
	 * @brief Drives mecanum wheels in tank style
	 *
	 * Intended for use in 'tank/west-coast/differential' style controls,
	 * where 1 stick controls the left side, and the other controls the right.
	 *
	 * @param[in] leftSpeedV The speed in which the left wheels move forward/backwards.
	 * @param[in] leftSpeedH The speed in which the left wheels move the robot left/right.
	 * @param[in] rightSpeedV The speed in which the right wheels move forward/backwards.
	 * @param[in] rightSpeedH The speed in which the right wheels move the robot left/right.
	 *
	 */
	void MecanumTankDrive(double leftSpeedV, double leftSpeedH, double rightSpeedV, double rightSpeedH);

	/**
	 * @brief Resets the drive encoders to read zero.
	 */
	void ResetEncoders();

	/**
	 * @brief Gets the left drive encoder.
	 */
	frc::Encoder &GetLeftEncoder();

	/**
	 * @brief Gets the right drive encoder.
	 */
	frc::Encoder &GetRightEncoder();

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
	frc::MotorControllerGroup m_left{m_frontLeft, m_rearLeft};
	frc::SlewRateLimiter<units::scalar> frontLeftFilter{0.5 / 1_s};
	frc::SlewRateLimiter<units::scalar> rearLeftFilter{0.5 / 1_s};

	frc::VictorSP m_frontRight;
	frc::VictorSP m_rearRight;
	frc::Encoder m_rightEncoder;
	frc::MotorControllerGroup m_right{m_frontRight, m_rearRight};
	frc::SlewRateLimiter<units::scalar> frontRightFilter{0.5 / 1_s};
	frc::SlewRateLimiter<units::scalar> rearRightFilter{0.5 / 1_s};

	// Drive Controller
	frc::MecanumDrive m_drive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};
};
