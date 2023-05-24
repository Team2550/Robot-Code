#include "sequences/BalanceAuto.h"

BalanceAuto::BalanceAuto(DriveSubsystem* subsystem) {
	AddCommands(DriveForwardTimed(-1.0, 0.35_s, subsystem),
		ArmHandTimed(ArmHandTimed::Value::kRelease, 2.0_s, subsystem), DriveForwardTimed(-0.6, 5.0_s, subsystem));
}
