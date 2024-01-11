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
	enum Control {kTank, kArcade, kMecanum, kMecanumTank}

	/**
	 * @brief Drive and controls
	 * 
	 * Control Types
	 * =============
	 * 
	 * kTank
	 * kArcade
	 * kMecanum
	 * kMecanumTank
	 * 
	 * @param[in] subsystem The subsystem from the DriveSubsytem to be used.
	 * @param[in] controlType Accepts one of 4 values to specify which control scheme is used.
	 */
	explicit Drive(DriveSubsystem* subsystem, Control controlType);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	Drive::Control m_controlType;

	// The driver's controller.
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };
};