#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/LaunchSubsystem.h>

#include <cmath>

class Launch : public frc2::CommandHelper<frc2::Command, Launch> {
public:
	/**
	 * @brief Creates a new Launch Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 */
	explicit Launch(LaunchSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	LaunchSubsystem* m_launch;
};