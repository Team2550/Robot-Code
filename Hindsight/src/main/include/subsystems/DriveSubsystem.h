#pragma once

#include <frc/ADIS16470_IMU.h>
#include <frc/Encoder.h>
#include <frc/PowerDistribution.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/kinematics/SwerveModulePosition.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>

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
	 * @brief Creates a new odometry object
	 *
	 * Uses imuAngle and pose to create an object for the robot to know it's
	 * rotation relative to the field
	 *
	 * @param[in] imuAngle The starting angle of the imu
	 * @param[in] pose The starting pose of the robot
	 *
	 */
	void initializeSwerveOdometry(frc::Rotation2d imuAngle, frc::Pose2d pose);

	/**
	 * @brief Drives a swerve robot with 'arcade' controls.
	 *
	 * Can **only** be used on a **swerve drivebase**
	 * 1 stick controls the movement, the other rotation
	 *
	 * @param[in] speedV The speed in which the robot moves forwards/backwards.
	 * @param[in] speedH The speed in which the robot moves left/right.
	 * @param[in] rotation The speed in which the direction the robot is facing is changed.
	 * @param[in] imuAngle The angle from the IMU, used to determine the robot's direction
	 *
	 * @todo The code is entirely unfinished.
	 *
	 */
	void SwerveDrive(units::meters_per_second_t speedV, units::meters_per_second_t speedH,
		units::radians_per_second_t rotation, units::angle::degree_t imuAngle);

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

	/**
	 * @brief Resets the imu to read zero.
	 */
	void ResetGyro();

	/**
	 * @brief Sets the yaw axis of the IMU.
	 *
	 * @param[in] imuAxis The axis to use for the yaw.
	 */
	void SetYawAxis(frc::ADIS16470_IMU::IMUAxis imuAxis);

	/**
	 * @brief Gets the current yaw of the IMU.
	 */
	units::angle::degree_t GetCurrentAngle();

private:
	// Motor Controllers
	frc::Spark m_frontLeft;
	frc::Spark m_rearLeft;
	frc::Encoder m_leftEncoder;
	frc::Translation2d m_frontLeftLocation;
	frc::Translation2d m_rearLeftLocation;
	frc::MotorControllerGroup m_left { m_frontLeft, m_rearLeft };

	frc::Spark m_frontRight;
	frc::Spark m_rearRight;
	frc::Encoder m_rightEncoder;
	frc::Translation2d m_frontRightLocation;
	frc::Translation2d m_rearRightLocation;
	frc::MotorControllerGroup m_right { m_frontRight, m_rearRight };

	frc::ADIS16470_IMU m_imu;

	// Drive Controller
	frc::DifferentialDrive m_differentialDrive { m_left, m_right };
	frc::MecanumDrive m_mecanumDrive { m_frontLeft, m_rearLeft, m_frontRight, m_rearRight };
	frc::SwerveDriveKinematics<4> m_kinematics { m_frontLeftLocation, m_frontRightLocation, m_rearLeftLocation,
		m_rearRightLocation };
};