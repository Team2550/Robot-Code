#pragma once

#include <cmath>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Commands.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/ScheduleCommand.h>
#include <subsystems/IntakeSubsystem.h>

class AutoPivot : public frc2::CommandHelper<frc2::Command, AutoPivot> {
public:
	/**
	 * @brief Creates a new Drive Command.
	 *
	 * @param[in] subsystem The subsytem to use.
	 */
	explicit AutoPivot(IntakeSubsystem* subsystem, bool up, int amount);

	void Initialize() override;

	void Execute() override;

	void End(bool interrupted) override;

	bool IsFinished() override;

private:
	IntakeSubsystem* m_intake;
	bool m_up;
	int m_amount;
};