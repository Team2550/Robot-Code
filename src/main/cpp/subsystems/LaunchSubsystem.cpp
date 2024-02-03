#include "subsystems/LaunchSubsystem.h"

using namespace LaunchConstants;

LaunchSubsystem::LaunchSubsystem()
	: m_pushMotor { kLaunchMotorPorts[0], rev::CANSparkMax::MotorType::kBrushless }
	, m_launchMotor { kLaunchMotorPorts[1], rev::CANSparkMax::MotorType::kBrushless } { }

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