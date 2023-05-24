// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/voltage.h>

#include <numbers>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or bool constants.  This should not be used for any other purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace DriveConstants {
constexpr int kLeftMotorPorts[] = { 0, 1 };
constexpr int kRightMotorPorts[] = { 2, 3 };

constexpr int kLeftEncoderPorts[] = { 0, 1 };
constexpr int kRightEncoderPorts[] = { 2, 3 };
constexpr bool kLeftEncoderReversed = false;
constexpr bool kRightEncoderReversed = true;

constexpr int kManiplulatorPort = 4;
constexpr int kManipulatorWinchPort = 5;
/// @brief The DIO port for the manipulator's limit switch.
constexpr int kManiplulatorLimitPort = 4;

constexpr int kEncoderCPR = 1024;
constexpr double kWheelDiameterInches = 6;
constexpr double kEncoderDistancePerPulse =
	// TODO: Fix this
	// Assumes the encoders are directly mounted on the wheel shafts (they aren't, we need to fix this)
	(kWheelDiameterInches * std::numbers::pi) / static_cast<double>(kEncoderCPR);
} // namespace DriveConstants

namespace AutoConstants {
constexpr auto kAutoTimeoutSeconds = 12_s;
constexpr auto kAutoShootTimeSeconds = 7_s;
} // namespace AutoConstants

/// @brief These are constants for handling driver input.
namespace OIConstants {
constexpr int kDriverControllerPort = 0;
constexpr int kArmControllerPort = 1;
} // namespace OIConstants
