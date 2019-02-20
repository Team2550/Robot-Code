#include "AutoController.h"
#include "Robot.h"
const float AUTO_STEER_STRENGTH = 1.3;
const float STRAIGHT_DECEL_MULT = 90;
const float ROTATE_DECEL_MULT = 100;

AutoController::AutoController(Robot* robot_) : robot(robot_)
{
	instructionSet.steps = NULL;
	instructionSet.count = 0;

	currentInstruction = 0;
	instructionStartTime = 0;
	instructionStartDistance = 0;
	instructionStartAngle = 0;
	instructionTargetAngle = 0;
}

AutoController::~AutoController()
{

}

void AutoController::Init(InstructionSet instructionSet)
{
	printf("recieved autonomous command!");
	timer.Reset();
	timer.Start();

	this->instructionSet.steps = instructionSet.steps;
	this->instructionSet.count = instructionSet.count;

	printf("%d", instructionSet.count);

	robot->driveBase.ResetDistance();
	robot->gyroscope.Reset();

	currentInstruction = 0;
	instructionStartTime = 0;
	instructionStartDistance = 0;
	instructionStartAngle = 0;
	instructionTargetAngle = 0;
}

bool AutoController::Execute()
{
	if (instructionSet.steps == NULL || currentInstruction >= instructionSet.count)
		return true;

	// Gets set to true if instruction is complete
	bool instructionCompleted = false;

	// Instruction Information
	Instruction inst = *(instructionSet.steps + currentInstruction);
	std::cout << "Left Speed: " << inst.leftSpeed << " Right Speed: " << inst.rightSpeed << std::endl;

	switch (inst.type)
	{
	case WAIT_TIME:
		inst.target += instructionStartTime;
	case WAIT_UNTIL:
		robot->driveBase.Drive(inst.leftSpeed, inst.rightSpeed);
		instructionCompleted = (timer.Get() >= inst.target);
		break;

	case DRIVE_DIST:
		inst.target += instructionStartDistance;
	case DRIVE_TO:
		std::cout << "Driving to " << inst.target << " and angle of " << instructionTargetAngle << std::endl;
		instructionCompleted = AutoDriveToDist( inst.leftSpeed, inst.rightSpeed, inst.target, instructionTargetAngle, inst.stopAtTarget );
		break;

	case ROTATE_DEG:
		inst.target += instructionTargetAngle;
	case ROTATE_TO:
		std::cout << "Rotating to " << inst.target << std::endl;
		instructionCompleted = AutoRotateToAngle( inst.leftSpeed, inst.rightSpeed, inst.target, inst.stopAtTarget );
		break;

	case RESET_DIST_0:
		robot->driveBase.ResetDistance();
		std::cout << "Reset dist" << std::endl;
		instructionCompleted = true;
		break;

	case DRIVE_UNTIL:
		if (doAmpTest && robot->driveBase.getAmps(robot->pdp) > Autonomous::AmpLimit)
			{
				printf("Amps too high! Stopping...\n");
				robot->driveBase.Stop();
			}
			else
			{
				robot->driveBase.Drive(.25f,.25f);
			}

	//case RESET_DIST_ULTRA:
	//	driveBase->ResetDistance(); // TODO: Add a way to reset the distance to the current ultrasonic reading
	//	driveBase->Stop();
	//	instructionCompleted = true;
	//	break;

	default:
		robot->driveBase.Stop();
	}

	if (instructionCompleted)
	{
		instructionStartTime = timer.Get();
		instructionStartDistance = GetCurrentDistance();
		instructionStartAngle = robot->gyroscope.GetAngle();

		if (inst.type == ROTATE_DEG || inst.type == ROTATE_TO)
			instructionTargetAngle = inst.target;

		currentInstruction++;
	}

	// Check if all instructions are complete
	if (currentInstruction >= instructionSet.count)
	{
		robot->driveBase.Stop();
		return true;
	}
	else
		return false;
}

bool AutoController::AutoDriveToDist( double leftSpeed, double rightSpeed, double targetDistance, double targetAngle, bool stopAtTarget )
{
	// Get sensor data
	double currentDistance = GetCurrentDistance(); // Average of left and right distances.
	printf("current distance: ");
	printf("%d", currentDistance);
	printf("target distance: ");
	printf("%d", targetDistance);
	double currentAngle = robot->gyroscope.GetAngle();

	// Get the angle that the robot has drifted from its target as a percentage out of 90 degrees
	double angleOffsetPercent = (currentAngle - targetAngle) / 10;

	// Limit angle offset to range of -10 to 10 (-100% to 100%)
	if (angleOffsetPercent > 1)
		angleOffsetPercent = 1;
	if (angleOffsetPercent < -1)
		angleOffsetPercent = -1;

	// Parabolic curve of speed scaling
	angleOffsetPercent *= pow(fabs(angleOffsetPercent), AUTO_STEER_STRENGTH - 1);

	// Scale the speed based on distance to target
	double speedMultiplier = 1;

	// Back up if passed target
	if (currentDistance > targetDistance)
	{
		speedMultiplier = -1;
	}

	// Set speed offset to the speed multiplied by the percent that the robot is to 90 degrees off target
	double leftSpeedMult = 1.0 - angleOffsetPercent * speedMultiplier;
	double rightSpeedMult = 1.0 + angleOffsetPercent * speedMultiplier;

	// If robot should stop after reaching target
	if (stopAtTarget)
	{
		// Distance to decelerate is greater for higher speeds
		double decelerateDistance = STRAIGHT_DECEL_MULT * pow((fabs(leftSpeed) + fabs(rightSpeed)) / 2, 2);

		// Slow down on start/approach
		if (fabs(targetDistance - currentDistance) < decelerateDistance)
			speedMultiplier *= fabs(targetDistance - currentDistance) / decelerateDistance;
		else if (fabs(timer.Get() - instructionStartTime) < .5)
			speedMultiplier *= 0.5 + fabs(timer.Get() - instructionStartTime);
	}

	// Prevent robot from driving too slowly
	if ((leftSpeed + rightSpeed) * 0.5 * fabs(speedMultiplier) < 0.25)
		speedMultiplier *= 0.25 / ((leftSpeed + rightSpeed) * 0.5 * fabs(speedMultiplier));

	robot->driveBase.Drive(leftSpeed * speedMultiplier * leftSpeedMult, rightSpeed * speedMultiplier * rightSpeedMult);

	// Returns true if distance to target is less than 2 (1/6 foot range)
	return abs( currentDistance - targetDistance ) < 2;
}

bool AutoController::AutoRotateToAngle( double leftSpeed, double rightSpeed, double targetAngle, bool stopAtTarget )
{
	//printf("rotating!!!");
	// If left and right speeds are equal, assume directions are meant to be opposite
	if (leftSpeed == rightSpeed)
		rightSpeed *= -1;

	// If speeds would cause robot to rotate counter-clockwise, invert them because the sign of speeds should rotate clockwise
	if (rightSpeed > leftSpeed)
	{
		rightSpeed *= -1;
		leftSpeed *= -1;
	}

	// Get sensor data
	double targetAngleOffset = targetAngle - robot->gyroscope.GetAngle();

	double speedMultiplier = 1;

	// Slow down robot on approach
	if (stopAtTarget)
	{
		double decelerateAngle = ROTATE_DECEL_MULT * pow((fabs(leftSpeed) + fabs(rightSpeed)) / 2, 2);

		if (fabs(targetAngleOffset) < decelerateAngle)
			speedMultiplier = fabs(targetAngleOffset) / decelerateAngle;
		else if (fabs(timer.Get() - instructionStartTime) < .5)
			speedMultiplier *= 0.5 + fabs(timer.Get() - instructionStartTime);
	}

	// Prevent robot from driving too slowly
	if (speedMultiplier < 0.5)
		speedMultiplier = 0.5;

	// Turn clockwise
	if ( targetAngleOffset > 4 )
		robot->driveBase.Drive(leftSpeed * speedMultiplier, rightSpeed * speedMultiplier);

	// Turn counter-clockwise
	else if ( targetAngleOffset < -4 )
		robot->driveBase.Drive(-leftSpeed * speedMultiplier, -rightSpeed * speedMultiplier);

	// Stop
	else if (stopAtTarget)
		robot->driveBase.Stop();


	// Return true if angle is within range of (targetAngle - 4, targetAngle + 4))
	return abs( targetAngleOffset ) < 4;
}

double AutoController::GetCurrentDistance()
{
	return (robot->driveBase.GetLeftDistance() + robot->driveBase.GetRightDistance()) / 2;
}
