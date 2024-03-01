#pragma once

#include <frc/XboxController.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/ClimbSubsystem.h>

#include <cmath>

class TeleClimb : public frc2::CommandHelper<frc2::Command, TeleClimb> {
public:
	/**
	 * @brief Creates a new Climbing Command
	 *
	 * @param[in] subsystem The subsytem to use.
	 * @param[in] controller Accepts a frc::XboxController* object, used to controll the movements.
	 */
	explicit TeleClimb(
		ClimbSubsystem* subsystem, frc::XboxController* controller, frc::XboxController* secondController);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	frc::XboxController* m_controller;
	frc::XboxController* m_secondController;
	ClimbSubsystem* m_climber;
};