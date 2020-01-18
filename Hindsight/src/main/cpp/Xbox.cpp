#include "Xbox.h"

Xbox::Xbox() : controller(0)
{}

bool Xbox::boost(){
	return controller.GetRawButton(lb);
}
bool Xbox::turtle(){
	return controller.GetRawButton(rb);
}

double Xbox::leftTankAxis(){
	return controller.GetRawAxis(leftY);
}

double Xbox::rightTankAxis(){
	return controller.GetRawAxis(rightY);
}