#pragma once

#include <frc/ADIS16470_IMU.h>
#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

class DriveSubsystem : public frc2::SubsystemBase {
public:
	DriveSubsystem();

	/***
	 * @brief Drives the robot using arcade controls.
	 *
	 * @param speed The speed to drive the robot.
	 * @param rotation The rotation to steer the robot to.
	 */
	void ArcadeDrive(double speed, double rotation);

	/***
	 * @brief Drives the robot using tank controls.
	 *
	 * @param leftSpeed The speed to run the left-side motors.
	 * @param rightSpeed The speed to run the right-side motors.
	 */
	void TankDrive(double leftSpeed, double rightSpeed);

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
	 * @brief Resets the drive encoders to read zero.
	 */
	void ResetEncoders();

	/**
	 * @brief Resets the imu to read zero.
	 */
	void ResetGyro();

	/**
	 * @brief Gets the left drive encoder.
	 */
	frc::Encoder& GetLeftEncoder();

	/**
	 * @brief Gets the right drive encoder.
	 */
	frc::Encoder& GetRightEncoder();

	/**
	 * Gets the average encoder distance between 2 encoders.
	 *
	 * @return the average of the 2 encoder readings.
	 */
	double GetAverageEncoderDistance();

	/// @brief Sets the yaw axis of the IMU.
	/// @param imuAxis The axis to use for the yaw.
	void SetYawAxis(frc::ADIS16470_IMU::IMUAxis imuAxis);

	/**
	 * @brief Gets the current yaw of the IMU.
	 */
	units::angle::degree_t GetCurrentAngle();

	/**
	 * @brief Drives the manipulator's winch.
	 * @param speed The speed to drive the winch (-1 to 1)
	 */
	void DriveWinch(double speed);

	/**
	 * Sets the output scalar.
	 *
	 * @param scale The value to scale the output by (0-1).
	 */
	void SetOutputScale(double scale);

private:
	// Motor Controllers
	frc::Spark m_frontLeft;
	frc::Spark m_rearLeft;
	frc::MotorControllerGroup m_left { m_frontLeft, m_rearLeft };

	frc::Spark m_frontRight;
	frc::Spark m_rearRight;
	frc::MotorControllerGroup m_right { m_frontRight, m_rearRight };

	frc::Spark m_manipulator;
	frc::Spark m_manipulatorWinch;
	frc::DigitalInput m_manipulatorLimit;

	// Pneumatics
	frc::DoubleSolenoid m_manipulatorSolenoid { frc::PneumaticsModuleType::CTREPCM, 0, 1 };

	// Encoders
	frc::Encoder m_leftEncoder;
	frc::Encoder m_rightEncoder;

	// Gyro
	frc::ADIS16470_IMU m_imu;

	// Drive Controller
	frc::DifferentialDrive m_drive { m_left, m_right };
};