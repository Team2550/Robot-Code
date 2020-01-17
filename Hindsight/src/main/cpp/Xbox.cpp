#include "Xbox.h"

Xbox::Xbox() : controller(0)
{}

bool Xbox::shoot(){
	return true;
}
bool Xbox::climb(){
	return true;
}
bool Xbox::autoAim(){
	return controller.GetRawButton(a);
}