#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/button/CommandXboxController.h>

#include <cmath>

#include "Constants.h"
#include "subsystems/DriveSubsystem.h"

class MoveArm : public frc2::CommandHelper<frc2::CommandBase, MoveArm> {
public:
	/***
	 * @brief Moves the manipulator
	 *
	 * @param upTrigger The trigger to use for moving up
	 * @param downTrigger The trigger to use for moving down
	 */
	explicit MoveArm(double upTrigger, double downTrigger, DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;

	double upTrigger;
	double downTrigger;
	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };
};