#include "Utility.h"
#include <WPILib.h>


/*!
 * \brief Applies the specified deadzone to value
 *
 * \param[in] value     The value to apply the deadzone to
 * \param[in] tolerance The deadzone to use
 * \return 0 if the absolute value of the given value is smaller than or
 * equal to tolerance; otherwise, the original value
 */
float Utility::Deadzone(float value, float tolerance)
{
	return fabs(value) <= tolerance ? 0 : value;
}

/*!
 * \brief Splits the given string where the delimiter is found
 *
 * \param[in] str       The string to split
 * \param[in] delimiter The delimiter to use
 * \return A vector containing the resulting strings
 */
std::vector<std::string> Utility::SplitString(std::string str, char delimiter)
{
	std::vector<std::string> substrings;
	std::string substr;

	for (unsigned int i = 0; i < str.length(); i++)
	{
		substr = "";

		while (str[i] != delimiter && i < str.length())
		{
			substr += str[i++];
		}

		substrings.push_back(substr);
	}

	return substrings;
}

/*!
 * \brief Converts a vector of strings to a vector of floats
 *
 * This works by calling stof() on every string in the vector. If for some
 * reason the string cannot be converted to a float, it is silently skipped.
 * \param[in] strs The strings to convert
 * \return A vector containing the resulting floats
 */
std::vector<float> Utility::StrVectorToFloatVector(std::vector<std::string> strs)
{
	std::vector<float> nums;
	float num;

	for (unsigned int i = 0; i < strs.size(); i++)
		try
		{
			num = stof(strs[i]);
			nums.push_back(num);
		}
		catch (...)
		{}

	return nums;
}

/*!
 * \brief Sets the the rumble of the given controller
 *
 * This allows setting a specific rumble value to a specific side
 * of a specific controller
 * \param[out] controller   The controller to set the rumble of
 * \param[in] rumbleSide   Which side of the controller to rumble
 * \param[in] rumbleAmount The intensity of the rumble, from 0 to 1
 */
void Utility::SetRumble(Joystick& controller, Utility::RumbleSide rumbleSide, float rumbleAmount)
{
	switch (rumbleSide)
	{
	case LEFT:
		controller.SetRumble(Joystick::kLeftRumble, rumbleAmount);
		break;
	case RIGHT:
		controller.SetRumble(Joystick::kRightRumble, rumbleAmount);
		break;
	case BOTH:
		controller.SetRumble(Joystick::kLeftRumble, rumbleAmount);
		controller.SetRumble(Joystick::kRightRumble, rumbleAmount);
		break;
	}
}
