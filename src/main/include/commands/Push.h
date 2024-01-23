#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/LaunchSubsystem.h>

#include <cmath>

class Push : public frc2::CommandHelper<frc2::CommandBase, Push> {
public:
	/**
	 * @brief Creates a new Push Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 */
	explicit Push(LaunchSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	LaunchSubsystem* m_launch;
};