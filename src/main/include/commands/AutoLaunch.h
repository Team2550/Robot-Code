#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/LaunchSubsystem.h>
#include <subsystems/IntakeSubsystem.h>

#include <cmath>

class AutoLaunch : public frc2::CommandHelper<frc2::Command, AutoLaunch> {
public:
	/**
	 * @brief Creates a new Launch Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 * @param[in] amount Time to run.
	 */
	explicit AutoLaunch(LaunchSubsystem* launchSubsystem, IntakeSubsystem* intakeSubsystem, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	LaunchSubsystem* m_launch;
	IntakeSubsystem* m_intake;
	int m_amount;
};