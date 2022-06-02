#include "DriveBase.h"

DriveBase::DriveBase(int leftFrontPort, int rightFrontPort,
					 int leftRearPort, int rightRearPort)
	: leftFrontMotor(leftFrontPort) /*Spark*/, rightFrontMotor(rightFrontPort) /*VictorSP*/,
	  leftRearMotor(leftRearPort) /*VictorSP*/, rightRearMotor(rightRearPort){ /*Spark*/ 

	leftFrontMotorValue = leftFrontPort;
	rightFrontMotorValue = rightFrontPort;
	leftRearMotorValue = leftRearPort;
	rightRearMotorValue = rightRearPort;
	
}
