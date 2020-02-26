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

<<<<<<< Updated upstream
=======
bool FlightStick::shoot(){
	return rightFlightStick.GetRawButton(1);
}

bool FlightStick::climb(){
	return rightFlightStick.GetRawButtonPressed(11);
}

>>>>>>> Stashed changes
double FlightStick::leftTankAxis(){
	return leftFlightStick.GetRawAxis(Y);
}

double FlightStick::rightTankAxis(){
	return rightFlightStick.GetRawAxis(Y);
}