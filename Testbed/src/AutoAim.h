/*
 * AutoAim.h
 *
 *  Created on: Jan 14, 2019
 *      Author: Team 2550
 */

//#include "Robot.h"
#include <iostream>
#include <iomanip>

#ifndef SRC_AUTOAIM_H_
#define SRC_AUTOAIM_H_

namespace Autonomous
{
	const float AmpLimit = 2;
}

class Robot;

class AutoAim{
private:
//	DriveBase driveBase;
//	UDP_Receiver udpReceiver;
	float baseSpeed;
//	PowerDistributionPanel pdp;
	Robot* robot;
public:
	AutoAim(Robot* robot);
	bool checkAutoAim(bool isSidePos, bool doAmpTest = false);

};



#endif /* SRC_AUTOAIM_H_ */
