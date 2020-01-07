#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <frc/WPILib.h>
#include <math.h>
#include "Utility.h"

class LimitSwitch
{
public:
	enum SignalState { LOW, HIGH };

	LimitSwitch( int port, SignalState stateWhenPushed );

	bool GetPushed();

private:
	DigitalInput sensor;

	SignalState stateWhenPushed;

};

#endif
