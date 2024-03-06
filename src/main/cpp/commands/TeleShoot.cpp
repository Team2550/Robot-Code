#include "commands/TeleShoot.h"

TeleShoot::TeleShoot(LaunchSubsystem* subsystem, frc::XboxController* controller)
	: m_launch(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleShoot::Initialize() { }

void TeleShoot::Execute() {
	if (m_controller->GetAButton()) {
		wait = wait + 1;
		m_controller->SetRumble(frc::GenericHID::kLeftRumble, 1);
		m_launch->LaunchRing();
		if (wait >= 40) {
			m_launch->PushRing();
		}
	} else if (m_controller->GetBButton()) {
		m_controller->SetRumble(frc::GenericHID::kRightRumble, 1);
		m_launch->IntakeRing();
	} else if (m_controller->GetXButton()) {
		m_controller->SetRumble(frc::GenericHID::kBothRumble, 0.3);
		m_launch->GentleRing();
	} else {
		wait = 0;
		m_controller->SetRumble(frc::GenericHID::kBothRumble, 0);
		m_launch->Stop();
	}
}

void TeleShoot::End(bool interrupted) { }

bool TeleShoot::IsFinished() { return false; }