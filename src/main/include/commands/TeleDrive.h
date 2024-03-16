#pragma once

#include <frc/XboxController.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/DriveSubsystem.h>

#include <cmath>

class TeleDrive : public frc2::CommandHelper<frc2::Command, TeleDrive> {
public:
	enum Control { kTank, kArcade, kMecanum, kMecanumField };

	/**
	 * @brief Creates a new Drive Command
	 *
	 * Control Types
	 * =============
	 *
	 * kTank
	 * kArcade
	 * kMecanum
	 * kMecanumField
	 *
	 * @param[in] subsystem The subsytem to use.
	 * @param[in] controlType Accepts one of 2 values to specify which control scheme is used.
	 * @param[in] controller Accepts a frc::XboxController* object, used to controll the movements.
	 */
	explicit TeleDrive(DriveSubsystem* subsystem, Control controlType, frc::XboxController* controller);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	double m_speedMult;
	TeleDrive::Control m_controlType;
	frc::XboxController* m_controller;
	DriveSubsystem* m_drive;
};