#include "Xbox.h"

Xbox::Xbox() : controller(0), secondaryController(1)
{}

bool Xbox::boost(){
	return controller.GetRawButton(rb);
}

bool Xbox::turtle(){
	return controller.GetRawButton(lb);
}

bool Xbox::intake(){
	return controller.GetRawButtonPressed(a);
}

bool Xbox::shoot(){
	return controller.GetRawButtonPressed(b);
}

bool Xbox::climb(){
	return secondaryController.GetRawButtonPressed(a);
}

double Xbox::winchSpeed(){
	if (secondaryController.GetRawButton(lb) && secondaryController.GetRawButton(rb)){
		return 0; // Safety feature -- keeps contradictory signals from being sent
	} else if (secondaryController.GetRawButton(lb) && !secondaryController.GetRawButton(rb)) {
		return 1;
	} else if (secondaryController.GetRawButton(rb) && !secondaryController.GetRawButton(lb)) {
		return -1;
	} else {
		return 0;
	}
}

double Xbox::leftTankAxis(){
	return controller.GetRawAxis(leftY);
}

double Xbox::rightTankAxis(){
	return controller.GetRawAxis(rightY);
}

double Xbox::shooterSpeedAxis(){
	return 0.5;
}

double Xbox::trenchSpeedAxis(){
	if (secondaryController.GetRawAxis(LT) > 0.2 || secondaryController.GetRawAxis(RT) > 0.2){
		if (secondaryController.GetRawAxis(LT) == secondaryController.GetRawAxis(RT)){
			return 0; // Safety feature -- keeps contradictory signals from being sent
		} else if (secondaryController.GetRawAxis(LT) > secondaryController.GetRawAxis(RT)) {
			return secondaryController.GetRawAxis(LT) * 0.42;
		} else if (secondaryController.GetRawAxis(RT) > secondaryController.GetRawAxis(LT)) {
			return secondaryController.GetRawAxis(RT) * -0.42;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}