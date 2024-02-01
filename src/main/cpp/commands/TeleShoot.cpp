#include "commands/TeleShoot.h"

TeleShoot::TeleShoot(LaunchSubsystem* subsystem)
	: m_launch(subsystem) {
	AddRequirements({ subsystem });
}

void TeleShoot::Initialize() { }

void TeleShoot::Execute() {

	if (m_driverController.GetAButton()) {
		m_driverController.SetRumble(frc::GenericHID::kLeftRumble, 1);
		m_launch->LaunchRing();
		m_launch->PushRing();
	}

	if (m_driverController.GetBButton()) {
		m_driverController.SetRumble(frc::GenericHID::kRightRumble, 1);
		m_launch->IntakeRing();
	}

	if (!m_driverController.GetAButton() && !m_driverController.GetBButton()) {
		m_driverController.SetRumble(frc::GenericHID::kBothRumble, 0);
		m_launch->Stop();
	}
}

void TeleShoot::End(bool interrupted) { }

bool TeleShoot::IsFinished() { return false; }