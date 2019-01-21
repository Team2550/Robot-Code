#include "DriveBase.h"

DriveBase::DriveBase(int leftMotorPort, int rightMotorPort,
					 int leftEncoderPortA, int leftEncoderPortB,
					 int rightEncoderPortA, int rightEncoderPortB,
					 double wheelCircumference, int encoderPulsesPerRotation) :
	leftMotor(leftMotorPort), rightMotor(rightMotorPort),
	leftEncoder(leftEncoderPortA, leftEncoderPortB, Encoder::EncodingType::k2X),
	rightEncoder(rightEncoderPortA, rightEncoderPortB, Encoder::EncodingType::k2X)
{
	leftMotor.SetInverted(false);
	rightMotor.SetInverted(true);

	// Set encoder reversal for one side
	leftEncoder.SetReverseDirection(false);
	rightEncoder.SetReverseDirection(true);

	// Distance per pulse from encoder.
	leftEncoder.SetDistancePerPulse(wheelCircumference / encoderPulsesPerRotation);
	rightEncoder.SetDistancePerPulse(wheelCircumference / encoderPulsesPerRotation);

	// Length of time needed to determine whether robot is stopped (seconds).
	leftEncoder.SetMaxPeriod(.1);
	rightEncoder.SetMaxPeriod(.1);

	// Minimum speed to determine if robot is stopped (distance units/second).
	leftEncoder.SetMinRate(1);
	rightEncoder.SetMinRate(1);

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
	if (leftMotor.GetInverted())
		return -leftMotor.Get();
	else
		return leftMotor.Get();
}

double DriveBase::GetRightSpeed()
{
	if (rightMotor.GetInverted())
		return -rightMotor.Get();
	else
		return rightMotor.Get();
}

void DriveBase::Drive(double leftSpeed, double rightSpeed)
{
	if (leftSpeed > 0)
		leftMotor.Set(leftSpeed * leftForwardTrim);
	else
		leftMotor.Set(leftSpeed * leftReverseTrim);

	if (rightSpeed > 0)
		rightMotor.Set(rightSpeed * rightForwardTrim);
	else
		rightMotor.Set(rightSpeed * rightReverseTrim);
}

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
	return leftEncoder.GetStopped() && rightEncoder.GetStopped();//it is red but it builds. Don't touch it. We don't know what is going on. We don't know how it works.
}

void DriveBase::ResetDistance()
{
	leftEncoder.Reset(); //it is red but it builds. Don't touch it. We don't know what is going on. We don't know how it works.
	rightEncoder.Reset();//it is red but it builds. Don't touch it. We don't know what is going on. We don't know how it works.
}

double DriveBase::GetLeftDistance()
{
	return leftEncoder.GetDistance();//it is red but it builds. Don't touch it. We don't know what is going on. We don't know how it works.
}

double DriveBase::GetRightDistance()
{
	return rightEncoder.GetDistance();//it is red but it builds. Don't touch it. We don't know what is going on. We don't know how it works.
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
void DriveBase::setReversed(bool reverse)
{
	isReversed = reverse;
}

/*!
 * \brief Tells which end of the Robot is the front
 *
 * \return True if and only if the back of the Robot is being treated as the front
 */
bool DriveBase::getReversed()
{
	return isReversed;
}

float DriveBase::getAmps(PowerDistributionPanel& pdp)
{
	return (pdp.GetCurrent(leftMotorPortValue) + pdp.GetCurrent(rightMotorPortValue)) / 2;
}


