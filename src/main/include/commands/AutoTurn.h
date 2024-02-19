#pragma once

#include <cmath>
#include <frc/DriverStation.h>
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
	 * @param[in] left Bool left if true right if false.
	 * @param[in] amount Time, 45 is roughly 180 degrees at 12.5V
	 * @param[in] ds DriverStation Object
	 */
	explicit AutoTurn(DriveSubsystem* subsystem, bool left, double amount, frc::DriverStation* ds);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	frc::DriverStation* m_ds;
	bool m_left;
	double m_amount;
};