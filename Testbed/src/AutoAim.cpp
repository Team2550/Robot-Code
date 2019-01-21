/*
 * AutoAim.cpp
 *
 *  Created on: Jan 14, 2019
 *      Author: Brayton Kerekffy
 */

#include "AutoAim.h"
#include "Robot.h"

AutoAim::AutoAim(Robot* robot_) : robot(robot_)//driveBase(0, 1, 0, 1, 2, 3, 6.07 * M_PI, 512) // Pulses per rotation is set by encoder DIP switch. 512 PPR uses DIP switch configuration 0001.
{
	baseSpeed = .4f;
}
bool AutoAim::checkAutoAim(bool isSidePos, bool doAmpTest)
{
	// Backup value of reversal to restore when finished. Set motor reversal to true (front = camera)
	bool wasReversed = robot->driveBase.getReversed();
	robot->driveBase.setReversed(true);

	// Get amps for checking if against wall
	double amps = robot->driveBase.getAmps(robot->pdp);
	printf(std::to_string(amps).c_str());
	printf("\n");

	// Initialize base speed
#ifndef PRACTICE_2017_ROBOT
	float baseSpeed = isSidePos ? 0.25 : 0.2;
#else
	float baseSpeed = 0.4;
#endif

	// Get vision data
	float data[UDP::DataCount];
	robot ->udpReceiver.getUDPData(data);

	printf("Aiming...\n");

	printf("X Angle: ");
	printf(std::to_string(data[UDP::Index::HorizAngle]).c_str());
	printf(", Dist: ");
	printf(std::to_string(data[UDP::Index::Distance]).c_str());
	printf("\n");

	bool atTarget = false;

	if (!robot ->udpReceiver.getUDPDataIsReal() || !robot ->udpReceiver.getUDPDataAge() > 2)
	{
		printf("Cannot see target! ");

		// If data is not real, than target was never seen. Move forward blindly.
		if (!robot ->udpReceiver.getUDPDataIsReal())
		{
			printf("Target never seen, moving forward...\n");

			// Stop moving forward if motors are no longer spinning
			if (doAmpTest && amps > Autonomous::AmpLimit)
			{
				printf("Amps too high! Stopping...\n");
				robot ->driveBase.Stop();

				atTarget = true;
			}
			else
			{
				robot ->driveBase.Drive(baseSpeed * 0.8);
			}
		}
		// If xOffset is greater than 15, than target was last seen to the right. Rotate right.
		else if (data[UDP::Index::HorizAngle] > 10)
		{
			printf("Target last seen on right, rotating right. \n");

			robot ->driveBase.Drive(baseSpeed, -baseSpeed);
		}
		// If xOffset is less than -15, than target was last seen to the left. Rotate left.
		else if (data[UDP::Index::HorizAngle] < -10)
		{
			printf("Target last seen on left, rotating left. \n");

			robot ->driveBase.Drive(-baseSpeed, baseSpeed);
		}
		// If nothing else applies, than target was last seen in front. Move forward.
		else
		{
			printf("Target last seen centered, moving forward...\n");

			// Stop moving forward if motors are no longer spinning
			if (doAmpTest && amps > Autonomous::AmpLimit)
			{
				printf("Amps too high! Stopping...\n");
				robot ->driveBase.Stop();

				atTarget = true;
			}
			else
			{
				robot ->driveBase.Drive(baseSpeed * 0.8);
			}
		}
	}
	else
	{
		// Target is more than 15 degrees to the right. Rotate right.
		if (data[UDP::Index::HorizAngle] > 10)
		{
			printf("Target is far right\n");

			robot ->driveBase.Drive(baseSpeed * 1.5, -baseSpeed * 1.5);
		}
		// Target is more than 5 degrees to the right. Rotate right and move forward.
		else if (data[UDP::Index::HorizAngle] > 3) // Move while rotating
		{
			printf("Target is slight right\n");

			robot ->driveBase.Drive(baseSpeed, baseSpeed * 0.5);
		}
		// Target is more than 15 degrees to the left. Rotate left.
		else if (data[UDP::Index::HorizAngle] < -7)
		{
			printf("Target is far left\n");

			robot ->driveBase.Drive(-baseSpeed * 1.5, baseSpeed * 1.5);
		}
		// Target is more than 5 degrees to the left. Rotate left and move forward.
		else if (data[UDP::Index::HorizAngle] < -3)
		{
			printf("Target is slight left\n");

			robot ->driveBase.Drive(baseSpeed * 0.5, baseSpeed);
		}
		// Target is about centered but is distant. Move forward.
		else if (data[UDP::Index::Distance] > 7)
		{
			printf("Target is distant\n");

			robot ->driveBase.Drive(baseSpeed);
		}
		// Target is about centered and close. Move forward slowly.
		else if (data[UDP::Index::Distance] > 7)
		{
			printf("Target is near\n");

			robot ->driveBase.Drive(baseSpeed * 0.8);
		}
		// Robot is at target. Stop.
		else
		{
			printf("At target\n");

			robot ->driveBase.Stop();
		}
	}

	robot ->driveBase.setReversed(wasReversed);

	return atTarget;
}



