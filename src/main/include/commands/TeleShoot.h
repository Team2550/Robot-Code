#pragma once

#include <frc/XboxController.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/button/CommandXboxController.h>
#include <subsystems/LaunchSubsystem.h>

#include <cmath>

class TeleShoot : public frc2::CommandHelper<frc2::CommandBase, TeleShoot> {
public:
	enum Control { kTank, kArcade };

	explicit TeleShoot(LaunchSubsystem* subsystem);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	frc2::CommandXboxController m_driverController { OIConstants::kDriverControllerPort };
	LaunchSubsystem* m_launch;
};