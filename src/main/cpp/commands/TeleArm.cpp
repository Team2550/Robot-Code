#include "commands/TeleArm.h"

TeleArm::TeleArm(ManipulatorSubsystem* subsystem, frc::XboxController* controller)
	: m_manipulator(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleArm::Initialize() { }

void TeleArm::Execute() {
	// Arm movement
	m_manipulator->MoveArm(m_controller->GetLeftTriggerAxis(), m_controller->GetRightTriggerAxis());

	// The winch is loosened as the arm moves up to prevent damage.
	// There should absolutly be a cleaner way to do this,
	// But I cannot think of one right now, so this it is.
	if (m_controller->GetLeftTriggerAxis() > m_controller->GetRightTriggerAxis()) {
		m_manipulator->DriveWinch(-0.2);
	} else if (m_controller->GetLeftTriggerAxis() == m_controller->GetRightTriggerAxis()) {
		m_manipulator->DriveWinch(0);
	}

	// Winch up for balance.
	if (m_controller->GetXButton()) {
		m_manipulator->DriveWinch(-0.5);
	} else {
		m_manipulator->DriveWinch(0.0);
	}

	// Pneumatic actuation of the Manipulator.
	if (m_controller->GetAButton()) {
		m_manipulator->ArmRelease();
	} else if (m_controller->GetBButton()) {
		m_manipulator->ArmGrab();
	} else {
		m_manipulator->ArmRest();
	}
}

void TeleArm::End(bool interrupted) { }

bool TeleArm::IsFinished() { return false; }