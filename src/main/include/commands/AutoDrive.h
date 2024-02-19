#pragma once

#include <cmath>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/DriveSubsystem.h>

class AutoDrive : public frc2::CommandHelper<frc2::Command, AutoDrive> {
public:
	/**
	 * @brief Creates a new Drive Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 */
	explicit AutoDrive(DriveSubsystem* subsystem, bool forward, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	bool m_forward;
	int m_amount;
};