#ifndef AUTOSTRATEGIES_H
#define AUTOSTRATEGIES_H

#include "AutoController.h"

namespace AUTO_STRATEGIES
{
	const float AUTO_DRIVE_SPEED = 0.5f; // Increased from 0.4 to better grip block while moving
	const float AUTO_BOOST_SPEED = 0.9f;
	const float AUTO_ROTATE_SPEED = 0.65f;

	const float ROBOT_WIDTH = 30.5f; // Without bumpers
	const float ROBOT_LENGTH = 28.0f; 

	const AutoController::Instruction LEFT_PLATFORM_STEPS[] =
	{
		//drive off the platform
		{AutoController::DRIVE_DIST, 6, true, AUTO_STRATEGIES::AUTO_DRIVE_SPEED},
		{AutoController::WAIT_TIME, 0.05},

		//rotate towards the left wall and drive until ~1ft away
		{AutoController::ROTATE_TO, 90, true, 0, AUTO_STRATEGIES::AUTO_ROTATE_SPEED},
		{AutoController::DRIVE_DIST, 8, true, AUTO_STRATEGIES::AUTO_BOOST_SPEED}


	};

	const AutoController::InstructionSet LEFT_PLATFORM = {LEFT_PLATFORM_STEPS, 4};
	const AutoController::PositionOptions LEFT_PLATFORM_OPTIONS = {&LEFT_PLATFORM, &LEFT_PLATFORM};

	const AutoController::Instruction SPIN_STEPS[] = 
	{
		{AutoController::ROTATE_TO, 90, true, 0, AUTO_STRATEGIES::AUTO_ROTATE_SPEED},
		{AutoController::ROTATE_TO, 0, true, 0, AUTO_STRATEGIES::AUTO_ROTATE_SPEED}
	};

	const AutoController::InstructionSet SPIN = {SPIN_STEPS, 2};
	const AutoController::PositionOptions SPIN_OPTIONS = {&SPIN, &SPIN};
	
	const AutoController::Instruction NOTHING_STEPS[] =
	{
		{}
	};
	const AutoController::InstructionSet NOTHING = {NOTHING_STEPS, 0};
	const AutoController::PositionOptions NOTHING_OPTIONS = {&NOTHING, &NOTHING};

}

#endif
