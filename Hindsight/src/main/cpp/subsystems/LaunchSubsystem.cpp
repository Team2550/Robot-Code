#include "subsystems/LaunchSubsystem.h"

using namespace LaunchConstants;

LaunchSubsystem::LaunchSubsystem()
	: m_launchMotor { kLaunchMotorPorts[0] }
    , m_pushMotor { kLaunchMotorPorts[1] }  { }

/*
 * Launch functions
 */
void LaunchSubsystem::LaunchRing() {
    m_launchMotor.Set(1);
    MotorSafety::Feed();
}

void LaunchSubsystem::PushRing() {
    m_pushMotor.Set(0.2);
    MotorSafety::Feed();
}
