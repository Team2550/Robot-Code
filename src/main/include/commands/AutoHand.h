#pragma once

#include <cmath>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/ManipulatorSubsystem.h>

class AutoHand : public frc2::CommandHelper<frc2::Command, AutoHand> {
public:
	/**
	 * @brief Creates a new Hand Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 * @param[in] open Open the Hand.
	 * @param[in] amount command cycles to run the command for.
	 */
	explicit AutoHand(ManipulatorSubsystem* subsystem, bool open, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	ManipulatorSubsystem* m_manipulator;
	bool m_open;
	int m_amount;
};