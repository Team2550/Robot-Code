#include "FlightStick.h"

FlightStick::FlightStick() : leftFlightStick(0), rightFlightStick(1) {}

bool FlightStick::boost() { return leftFlightStick.GetRawButton(1); }

bool FlightStick::turtle() { return rightFlightStick.GetRawButton(1); }

bool FlightStick::intake() { return rightFlightStick.GetRawButtonPressed(3); }

double FlightStick::leftTankAxis() { return leftFlightStick.GetRawAxis(Y); }

double FlightStick::rightTankAxis() { return rightFlightStick.GetRawAxis(Y); }