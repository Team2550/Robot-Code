#include "FlightStick.h"

FlightStick::FlightStick() : leftFlightStick(0),
                   rightFlightStick(1)
{}

bool FlightStick::boost(){
	return leftFlightStick.GetRawButton(1);
}

bool FlightStick::turtle(){
	return rightFlightStick.GetRawButton(1);
}

bool FlightStick::intake(){
	return rightFlightStick.GetRawButtonPressed(3);
}

bool FlightStick::shoot(){
	return rightFlightStick.GetRawButton(1);
}

bool FlightStick::climb(){
	return rightFlightStick.GetRawButtonPressed(11);
}

bool FlightStick::winchCCW(){
	return leftFlightStick.GetRawButtonPressed(4);
}

bool FlightStick::winchCW(){
	return rightFlightStick.GetRawButton(4);
}

double FlightStick::leftTankAxis(){
	return leftFlightStick.GetRawAxis(Y);
}

double FlightStick::rightTankAxis(){
	return rightFlightStick.GetRawAxis(Y);
}

double FlightStick::shooterSpeedAxis(){
	return 0.5;
}