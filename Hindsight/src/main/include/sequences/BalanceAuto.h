#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "commands/ArmHand.h"
#include "commands/DriveForward.h"
#include "commands/DriveForwardTimed.h"
#include "commands/DriveTurn.h"
#include "commands/WaitCommand.h"
#include "subsystems/DriveSubsystem.h"
#include <commands/ArmHandTimed.h>

class BalanceAuto : public frc2::CommandHelper<frc2::SequentialCommandGroup, BalanceAuto> {
public:
	BalanceAuto(DriveSubsystem* subsystem);

private:
	DriveSubsystem* m_drive;
};