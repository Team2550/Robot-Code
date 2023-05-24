#pragma once

#include <frc/ADIS16470_IMU.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/WaitCommand.h>

#include <cmath>

#include "subsystems/DriveSubsystem.h"

class DriveTurn : public frc2::CommandHelper<frc2::CommandBase, DriveTurn> {
public:
	/**
	 * Creates a new DriveTurn.
	 *
	 * @param speed The speed at which the robot will drive.
	 * @param turnheading The head the robot will turn to.
	 * @param drive The drive subsystem on which this command will run.
	 */
	explicit DriveTurn(double speed, double turnheading, DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	double m_turnheading;
	double target;
	double m_speed;
	bool m_isComplete = false;

	// The gain for a simple P loop
	double kP = 0.5;

	// The heading of the robot when starting the motion
	double heading;
};