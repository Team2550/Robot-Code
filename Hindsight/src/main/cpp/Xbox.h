#ifndef XBOX_H
#define XBOX_H

#include "Input.h"
#include <frc/Joystick.h>

class Xbox : public Input {
  public:
	Xbox();
	bool boost();
	bool turtle();
	bool intake();
	double leftTankAxis();
	double rightTankAxis();

  private:
	frc::Joystick controller;
	const uint32_t a = 1;
	const uint32_t b = 2;
	const uint32_t x = 3;
	const uint32_t y = 4;

	const uint32_t lb = 5;
	const uint32_t rb = 6;

	const uint32_t back = 7;
	const uint32_t start = 8;

	const uint32_t leftPush = 9;
	const uint32_t rightPush = 10;

	// Axes (not the slashy kind)

	const uint32_t leftX = 0;
	const uint32_t leftY = 1;

	const uint32_t rightX = 4;
	const uint32_t rightY = 5;

	const uint32_t LT = 2;
	const uint32_t RT = 3;
	const uint32_t dpadX = 6;
};

#endif
