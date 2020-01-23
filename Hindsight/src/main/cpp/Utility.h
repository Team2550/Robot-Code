#ifndef UTILITY_H
#define UTILITY_H

#include <frc/Joystick.h>
#include <math.h>
#include <vector>
#include <string>
#include "Xbox.h"

using namespace frc;

namespace Utility
{
	enum RumbleSide { LEFT, RIGHT, BOTH };

	/*=================================================
	Name: deadzone
	Desc: Zeroes out values within a certain "deadzone"
	Arguments:
		value (IO): value to deadzone
		tolerance (I): deadzone
	Return:
		none
	=================================================*/
	float Deadzone(float value, float tolerance = 0.2);

	/*=================================================
	Name: splitString
	Desc: Splits a string at delimiters
	Arguments:
		str (I): String to split
		delimiter (I): Delimiter to split at
	Return:
		Vector containing substrings of original string
	=================================================*/
	std::vector<std::string> SplitString(std::string str, char delimiter);

	/*=================================================
	Name: strVectorToFloatVector
	Desc: Converts a vector of strings to a vector of floats
	Arguments:
		strs (I): Vector of strings
	Return:
		Vector of floats
	=================================================*/
	std::vector<float> StrVectorToFloatVector(std::vector<std::string> strs);

	/*=================================================
	Name: setRumble
	Desc: Rumbles an xbox controller
	Arguments:
		controller   (I): controller to rumble
		rumbleSide   (I): side to rumble
		rumbleAmount (I): rumble force [0, 1]
	Return:
		none
	=================================================*/
	void SetRumble(Joystick& controller, RumbleSide rumbleSide, float rumbleAmount);

}

#endif
