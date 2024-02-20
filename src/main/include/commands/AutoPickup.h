#pragma once

#include <cmath>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/DriveSubsystem.h>
#include <subsystems/IntakeSubsystem.h>

class AutoPickup : public frc2::CommandHelper<frc2::Command, AutoPickup> {
public:
	/**
	 * @brief Creates a new Drive Command.
	 *
	 * @param[in] launchSubsystem The Launch subsystem to use.
	 * @param[in] intakeSubsystem The Intake subsystem to use.
	 * @param[in] amount command cycles to run the command for.
	 */
	explicit AutoPickup(IntakeSubsystem* intakeSubsystem, DriveSubsystem* driveSubsystem, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	IntakeSubsystem* m_intake;
    DriveSubsystem* m_drive;
	int m_amount;
};