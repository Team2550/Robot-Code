// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/time.h>
#include <units/voltage.h>

#include <numbers>

/**
 * @brief Contains motor port, encoder port values, and motor locations
 */
namespace DriveConstants {
    constexpr int kLeftMotorPorts[] = { 0, 1 };
    constexpr int kRightMotorPorts[] = { 2, 3 };

    constexpr int kLeftEncoderPorts[] = { 0, 1 };
    constexpr int kRightEncoderPorts[] = { 2, 3 };
    constexpr bool kLeftEncoderReversed = false;
    constexpr bool kRightEncoderReversed = true;
} // namespace DriveConstants

namespace LaunchConstants {
    constexpr int kLaunchMotorPorts[] = { 4, 5 };
    constexpr int kLightPorts[] = { 0, 1 };
}

/**
 * @brief Contains the length of time for auto
 */
namespace AutoConstants {
    constexpr auto kAutoTimeoutSeconds = 12_s;
    constexpr auto kAutoShootTimeSeconds = 7_s;
} // namespace AutoConstants

/**
 * @brief Contains the ports used for controlers and deadzone
 */
namespace OIConstants {
    constexpr int kDriverControllerPort = 0;
    constexpr double kDeadzone = 0.2;
} // namespace OIConstants
