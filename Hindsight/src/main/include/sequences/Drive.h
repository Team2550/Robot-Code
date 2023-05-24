#pragma once

#include <frc/PowerDistribution.h>
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

class Drive : public frc2::CommandHelper<frc2::CommandBase, Drive> {
public:
	/***
	 * @brief Drive and controls
	 */
	explicit Drive(DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;

	double m_speed;
	double m_speedMult = 0.5;
	double m_rotation;
	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };
	frc2::CommandXboxController m_armController { OIConstants::kArmControllerPort };
};