#pragma once

#include <frc/XboxController.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/LaunchSubsystem.h>

#include <cmath>

class TeleShoot : public frc2::CommandHelper<frc2::CommandBase, TeleShoot> {
public:
	/**
	 * @brief Creates a new Shooter Command
	 *
	 * @param[in] subsystem The subsytem to use.
	 * @param[in] controller Accepts a frc::XboxController* object, used to controll the movements.
	 */
	explicit TeleShoot(LaunchSubsystem* subsystem, frc::XboxController* controller);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	frc::XboxController* m_controller;
	LaunchSubsystem* m_launch;
};