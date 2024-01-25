#include "subsystems/LaunchSubsystem.h"

using namespace LaunchConstants;

LaunchSubsystem::LaunchSubsystem()
	: m_pushMotor { kLaunchMotorPorts[0] }
	, m_launchMotor { kLaunchMotorPorts[1] }
	, m_redLight { kLightPorts[0] }
	, m_blueLight { kLightPorts[1] } { }

/*
 * Launch functions
 */
void LaunchSubsystem::LaunchRing() { m_launchMotor.Set(1); }

void LaunchSubsystem::PushRing() { m_pushMotor.Set(1); }

void LaunchSubsystem::IntakeRing() {
	m_launchMotor.Set((-0.5));
	m_pushMotor.Set((-0.25));
}

void LaunchSubsystem::Stop() {
	m_launchMotor.Set(0);
	m_pushMotor.Set(0);
}

void LaunchSubsystem::RedLight(bool State) {
	if (State) {
		m_redLight.Set(1);
	} else {
		m_redLight.Set(0);
	}
}

void LaunchSubsystem::BlueLight(bool State) {
	if (State) {
		m_blueLight.Set(1);
	} else {
		m_blueLight.Set(0);
	}
}
