#include "subsystems/IntakeSubsystem.h"

using namespace IntakeConstants;

IntakeSubsystem::IntakeSubsystem()
	: m_intakePivot { kIntakePivot }
	, m_intakeMotor { kIntakeMotor } { }

/*
 * Intake functions
 */
void IntakeSubsystem::IntakeRing() { m_intakeMotor.Set(1); }

void IntakeSubsystem::ExpellRing() { m_intakeMotor.Set(-1); }

void IntakeSubsystem::GentleRing() { m_intakeMotor.Set(-0.7); }

void IntakeSubsystem::StopIntake() { m_intakeMotor.Set(0); }

void IntakeSubsystem::PivotIntake(double upSpeed, double downSpeed) {
	if (fabs(upSpeed) < OIConstants::kDeadzone)
		upSpeed = 0;
	if (fabs(downSpeed) < OIConstants::kDeadzone)
		downSpeed = 0;

	m_intakePivot.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, (upSpeed - downSpeed));
}
