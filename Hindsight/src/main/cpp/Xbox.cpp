#include "Xbox.h"

Xbox::Xbox() : controller(0), secondaryController(1)
{}

bool Xbox::boost(){
	return controller.GetRawButton(lb);
}

bool Xbox::turtle(){
	return controller.GetRawButton(rb);
}

bool Xbox::intake(){
	return controller.GetRawButtonPressed(a);
}

bool Xbox::shoot(){
	return controller.GetRawButtonPressed(b);
}

bool Xbox::climb(){
	return controller.GetRawButtonPressed(back);
}

bool Xbox::winchCW(){
	return secondaryController.GetRawButton(lb);
}

bool Xbox::winchCCW(){
	return secondaryController.GetRawButton(rb);
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