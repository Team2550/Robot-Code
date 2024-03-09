#include "commands/TeleArm.h"

TeleArm::TeleArm(ManipulatorSubsystem* subsystem, frc::XboxController* controller)
	: m_manipulator(subsystem)
	, m_controller(controller) {
	AddRequirements({ subsystem });
}

void TeleArm::Initialize() { }

void TeleArm::Execute() {
	// Arm movement
	if (m_controller->GetLeftTriggerAxis() < m_controller->GetRightTriggerAxis()) {
		m_manipulator->MoveArm(-m_controller->GetRightTriggerAxis());
	} else {
		if (m_controller->GetLeftTriggerAxis() > m_controller->GetRightTriggerAxis()) {
			m_manipulator->MoveArm(m_controller->GetLeftTriggerAxis());
			m_manipulator->DriveWinch(-0.2);
		};
	}
	if (m_controller->GetLeftTriggerAxis() == m_controller->GetRightTriggerAxis()) {
		m_manipulator->MoveArm(0.0);
		m_manipulator->DriveWinch(0);
	}

	// THIS IS SO JANK!!!
	// I would fully rewrite this is I weren't on a time crunch.
	// The implementation in the 2024 bot is much much nicer.
	// use that instead.
	// - G

	// Winch when button
	if (m_controller->GetXButton()) {
		m_manipulator->DriveWinch(-0.5);
	} else if (m_controller->GetYButton()) {
		m_manipulator->DriveWinch(-0.1);
	} else {
		m_manipulator->DriveWinch(0.0);
	}

	// This is labled ArmTask, but it really is HandTask
	if (m_controller->GetAButton() == 1 && m_controller->GetBButton() == 0) {
		m_manipulator->ArmRelease();
	}
	if (m_controller->GetBButton() == 1 && m_controller->GetAButton() == 0) {
		m_manipulator->ArmGrab();
	}
	if (m_controller->GetBButton() == 0 && m_controller->GetAButton() == 0) {
		m_manipulator->ArmRest();
	}
}

void TeleArm::End(bool interrupted) { }

bool TeleArm::IsFinished() { return false; }