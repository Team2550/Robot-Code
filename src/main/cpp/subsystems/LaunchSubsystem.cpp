#include "subsystems/LaunchSubsystem.h"

using namespace LaunchConstants;

LaunchSubsystem::LaunchSubsystem()
	: m_launchMotor { kLaunchMotorPorts[0] }
	, m_pushMotor { kLaunchMotorPorts[1] } { }

/*
 * Launch functions
 */
void LaunchSubsystem::LaunchRing() { m_launchMotor.Set(1); }

void LaunchSubsystem::PushRing() { m_pushMotor.Set(1); }

void LaunchSubsystem::IntakeRing() {
	m_launchMotor.Set((-0.5));
	m_pushMotor.Set((-1));
}

void LaunchSubsystem::Stop() {
	m_launchMotor.Set(0);
	m_pushMotor.Set(0);
}
