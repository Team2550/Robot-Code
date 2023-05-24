#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/WaitCommand.h>

#include <chrono>
#include <cmath>

#include "subsystems/DriveSubsystem.h"

class DriveForwardTimed : public frc2::CommandHelper<frc2::CommandBase, DriveForwardTimed> {
   public:
	/**
	 * Creates a new DriveForwardTimed.
	 *
	 * @param speed The speed at which the robot will drive
	 * @param time 	The amount of time the robot will drive.
	 * @param drive The drive subsystem on which this command will run
	 */
	explicit DriveForwardTimed(double speed, units::second_t time, DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

   private:
	DriveSubsystem* m_drive;
	int m_msOccurred = 0;
	int m_desiredMs;

	double m_speed;

	// The gain for a simple P loop
	double kP = 0.5;

	// The heading of the robot when starting the motion
	double heading;
};