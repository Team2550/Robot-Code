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

class ArmHand : public frc2::CommandHelper<frc2::CommandBase, ArmHand> {
public:
	enum Value { kGrab, kRelease };
	/***
	 * @brief Moves the manipulator
	 *
	 * @param value The direction to actuate
	 */
	explicit ArmHand(Value value, DriveSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	DriveSubsystem* m_drive;
	ArmHand::Value m_value;
};