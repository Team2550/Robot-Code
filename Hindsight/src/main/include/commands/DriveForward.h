#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/WaitCommand.h>

#include <cmath>

#include "subsystems/DriveSubsystem.h"

class DriveForward : public frc2::CommandHelper<frc2::CommandBase, DriveForward> {
   public:
	/**
	 * Creates a new DriveForward.
	 *
	 * @param speed The speed at which the robot will drive.
	 * @param distance The distance the robot will drive in meters.
	 * @param drive The drive subsystem on which this command will run.
	 */
	explicit DriveForward(double speed, units::meter_t distance, DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

   private:
	DriveSubsystem* m_drive;
	/// @brief The internal distance in inches (the encoders give this to us.)
	/// Yes, I do know it's dumb.
	double m_distance;
	double m_speed;

	// The gain for a simple P loop
	double kP = 0.5;

	// The heading of the robot when starting the motion
	double heading;
};