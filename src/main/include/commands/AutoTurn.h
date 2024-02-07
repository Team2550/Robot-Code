#pragma once

#include <cmath>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/DriveSubsystem.h>

class AutoTurn : public frc2::CommandHelper<frc2::Command, AutoTurn> {
public:
	/**
	 * @brief Creates a new Turn Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 */
	explicit AutoTurn(DriveSubsystem* subsystem, bool left, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	bool m_left;
	int m_amount;
};