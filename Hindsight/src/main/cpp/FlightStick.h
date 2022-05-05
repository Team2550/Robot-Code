#ifndef FLIGHTSTICK_H
#define FLIGHTSTICK_H

#include "Input.h"
#include <frc/Joystick.h>

class FlightStick : public Input {
  public:
	FlightStick();
	bool boost();
	bool turtle();
	bool intake();
	double leftTankAxis();
	double rightTankAxis();

  private:
	frc::Joystick leftFlightStick;
	frc::Joystick rightFlightStick;

	// Axes (not the slashy kind)

	const uint32_t X = 0;
	const uint32_t Y = 1;
	const uint32_t Z = 2;
};

#endif
