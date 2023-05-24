#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/DriveSubsystem.h>

#include <cmath>

class WaitCommand : public frc2::CommandHelper<frc2::CommandBase, WaitCommand> {
public:
	/**
	 * Creates a new WaitCommand.
	 *
	 * @param time 	The amount of time that will be waited.
	 */
	explicit WaitCommand(units::second_t time);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	int m_msOccurred = 0;
	int m_desiredMs;

	DriveSubsystem* m_drive;
};