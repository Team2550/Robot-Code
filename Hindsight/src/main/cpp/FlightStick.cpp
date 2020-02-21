#include "FlightStick.h"

FlightStick::FlightStick() : leftFlightStick(0), rightFlightStick(1)
{}

bool FlightStick::boost(){
	return leftFlightStick.GetRawButton(2);
}

bool FlightStick::turtle(){
	return rightFlightStick.GetRawButton(2);
}

bool FlightStick::intake(){
	return rightFlightStick.GetRawButtonPressed(3);
}

bool FlightStick::shoot(){
	return rightFlightStick.GetRawButton(1);
}

double FlightStick::leftTankAxis(){
	return leftFlightStick.GetRawAxis(Y);
}

double FlightStick::rightTankAxis(){
	return rightFlightStick.GetRawAxis(Y);
}

double FlightStick::shooterSpeedAxis(){
	std::cout << "Shooter Motor Speed: " << rightFlightStick.GetRawAxis(Z) << std::endl;
	return rightFlightStick.GetRawAxis(Z);
}