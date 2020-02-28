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

double FlightStick::winchSpeed(){
	if (rightFlightStick.GetRawButton(4) && leftFlightStick.GetRawButtonPressed(4)){
		return 0; // Safety feature -- keeps contradictory signals from being sent
	} else if (rightFlightStick.GetRawButton(4) && !leftFlightStick.GetRawButtonPressed(4)) {
		return 1;
	} else if (leftFlightStick.GetRawButton(4) && !rightFlightStick.GetRawButton(4)) {
		return -1;
	} else {
		return 0;
	}
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

double FlightStick::trenchSpeedAxis(){
	if (rightFlightStick.GetRawButton(11) && rightFlightStick.GetRawButton(10)){
		return 0; // Safety feature -- keeps contradictory signals from being sent
	} else if (rightFlightStick.GetRawButton(11) && !rightFlightStick.GetRawButton(10)) {
		return 1;
	} else if (rightFlightStick.GetRawButton(10) && !rightFlightStick.GetRawButton(11)) {
		return -1;
	} else {
		return 0;
	}
}