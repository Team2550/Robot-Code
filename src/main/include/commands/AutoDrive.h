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
	 * @param[in] speed The speed to move the robot.
	 * @param[in] amount command cycles to run the command for.
	 */
	explicit AutoDrive(DriveSubsystem* subsystem, double speed, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	double m_speed;
	int m_amount;
};