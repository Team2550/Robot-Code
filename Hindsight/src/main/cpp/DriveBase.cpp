#include "DriveBase.h"

DriveBase::DriveBase(int leftMotorPort, int rightMotorPort,
					 int leftEncoderPortA, int leftEncoderPortB,
					 int rightEncoderPortA, int rightEncoderPortB,
					 double wheelCircumference, int encoderPulsesPerRotation) :
	leftMotor(leftMotorPort), rightMotor(rightMotorPort),
	leftEncoder(leftEncoderPortA, leftEncoderPortB, Encoder::EncodingType::k2X),
	rightEncoder(rightEncoderPortA, rightEncoderPortB, Encoder::EncodingType::k2X),
{
	leftMotor.SetInverted(false);
	rightMotor.SetInverted(false);

	// Set encoder reversal for one side
	leftEncoder.SetReverseDirection(false);
	rightEncoder.SetReverseDirection(false);

	// Distance per pulse from encoder.
	leftEncoder.SetDistancePerPulse(wheelCircumference / encoderPulsesPerRotation);
	rightEncoder.SetDistancePerPulse(wheelCircumference / encoderPulsesPerRotation);

	// Length of time needed to determine whether robot is stopped (seconds).
	leftEncoder.SetMaxPeriod(.1);
	rightEncoder.SetMaxPeriod(.1);

	// Minimum speed to determine if robot is stopped (distance units/second).
	leftEncoder.SetMinRate(1);
	rightEncoder.SetMinRate(1);

	//leftController.setPID(K_P, K_I, K_D);

	leftForwardTrim = 1;
	rightForwardTrim = 1;
	leftReverseTrim = 1;
	rightReverseTrim = 1;

	rightMotorPortValue = rightMotorPort;
	leftMotorPortValue = leftMotorPort;
	leftEncoderPortAValue = leftEncoderPortA;
	leftEncoderPortBValue = leftEncoderPortB;
	rightEncoderPortAValue = rightEncoderPortA;
	rightEncoderPortBValue = leftEncoderPortB;
	wheelCircumferenceValue = wheelCircumference;
	encoderPulsesPerRotationValue = encoderPulsesPerRotation;
}

double DriveBase::GetLeftSpeed()
{
	return leftMotor.GetInverted() ? leftMotor.Get() : -leftMotor.Get();
}

double DriveBase::GetRightSpeed()
{
	return rightMotor.GetInverted() ? rightMotor.Get() : -rightMotor.Get();
}

void DriveBase::Drive(double leftSpeed, double rightSpeed)
{

	/* Call calculate on the PID controllers */
	//
	//	Change speed to setpoint in variable names
	//

	//std::cout << leftController.Calculate(leftEncoder.GetDistance(), 0.1) << endl;
	//std::cout << rightController.Calculate(rightEncoder.GetDistance(), 0.1) << endl;

	leftMotor.Set(leftController.Calculate(leftEncoder.GetDistance(), leftSpeed));
	rightMotor.Set(rightController.Calculate(rightEncoder.GetDistance(), rightSpeed));
}

//
//	Convienience function for same speed to both motors. 
//
//	Deprecated.
//
void DriveBase::Drive(double speed)
{
	Drive(speed, speed);
}

void DriveBase::Stop()
{
	Drive(0, 0);
}

bool DriveBase::IsStopped()
{
	return leftEncoder.GetStopped() && rightEncoder.GetStopped();
}

void DriveBase::ResetDistance()
{
	leftEncoder.Reset(); 
	rightEncoder.Reset();
}

double DriveBase::GetLeftDistance()
{
	return leftEncoder.GetDistance();
}

double DriveBase::GetRightDistance()
{
	return rightEncoder.GetDistance();
}

void DriveBase::SetTrim(float leftForwardTrim, float rightForwardTrim, float leftReverseTrim, float rightReverseTrim)
{
	this->leftForwardTrim = leftForwardTrim;
	this->rightForwardTrim = rightForwardTrim;
	this->leftReverseTrim = leftReverseTrim;
	this->rightReverseTrim = rightReverseTrim;
}
/*!
 * \brief Changes which end of the Robot is the front
 *
 * \param[in] reverse Whether or not the back of the Robot should be considered the front
 */

//
//	FIX CAPTIALIZATION!
//

void DriveBase::SetReversed(bool reverse)
{
	isReversed = reverse;
}

/*!
 * \brief Tells which end of the Robot is the front
 *
 * \return True if and only if the back of the Robot is being treated as the front
 */
bool DriveBase::GetReversed()
{
	return isReversed;
}

float DriveBase::GetAmps(PowerDistributionPanel& pdp)
{
	return (pdp.GetCurrent(leftMotorPortValue) + pdp.GetCurrent(rightMotorPortValue)) / 2;
}

