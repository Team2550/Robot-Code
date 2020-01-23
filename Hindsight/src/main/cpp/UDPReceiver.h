#ifndef UDP_R_H
#define UDP_R_H

#include <frc/Timer.h>
#include <iostream>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "Utility.h"

//these should be changed to constants instead of #defines
#define BUFSIZE      2048
#define SERVICE_PORT 8890	/* hard-coded port number */

namespace UDP
{
	const int MaxPacketsFlush = 20;

	const int DataCount = 6;

	namespace Index
	{
		const int PercentMatch = 0;
		const int Distance = 1;
		const int XOffset = 2;
		const int YOffset = 3;
		const int HorizAngle = 4;
		const int VertAngle = 5;
	}
}

class UDPReceiver {

private:
	int ourSocket;
	struct sockaddr_in myAddress;
	struct sockaddr_in remoteAddress;
	socklen_t addressLength = sizeof(remoteAddress);
	char buffer[BUFSIZE];
	float newestUDPData[UDP::DataCount] = {-1, -1, -1, -1, -1, -1};
	bool isRealData = false;
	Timer UDPAgeTimer;
	int createUDPSocket();
public:
	UDPReceiver();

	bool checkUDP();
	void getUDPData(float data[]);
	double getUDPDataAge();
	bool getUDPDataIsReal();
	void clearUDPSocket();
	void getTeleopUDPData();
};


#endif
