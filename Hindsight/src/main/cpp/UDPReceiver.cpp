#include "UDPReceiver.h"

UDPReceiver::UDPReceiver()
{
	createUDPSocket();

	UDPAgeTimer.Start();
}

/*================================================
Name: getUDPData
Desc: Returns the most recent UDP data
Arguments:
	none
Return:
	Array of ints from UDP
================================================*/
void UDPReceiver::getUDPData(float data[])
{
	memcpy(data, newestUDPData, sizeof(newestUDPData));
}

/*================================================
Name: getUDPDataAge
Desc: Returns the age of the UDP data
Arguments:
	none
Return:
	Seconds since data was last received
================================================*/
// NOTE: this should probably return the proper units.
double UDPReceiver::getUDPDataAge()
{
	return double(UDPAgeTimer.Get());
}

/*================================================
Name: getUDPDataIsReal
Desc: Returns whether or not the current data is real or a placeholder
Arguments:
	none
Return:
	True if real, false if placeholder
================================================*/
bool UDPReceiver::getUDPDataIsReal()
{
	return isRealData;
}

/*================================================
Name: createUDPSocket
Desc: Creates UDP socket
Arguments:
	none
Return:
	0 if success, 1 if failed
================================================*/
int UDPReceiver::createUDPSocket()
{
	if ((ourSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	/* bind the socket to any valid IP address and a specific port */
	memset((char *) &myAddress, 0, sizeof(myAddress));
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddress.sin_port = htons(SERVICE_PORT);

	if (bind(ourSocket, (struct sockaddr *) &myAddress, sizeof(myAddress)) < 0) {
		perror("bind failed");
		return 1;
	}

	return 0;
}

/*================================================
Name: checkUDP
Desc: Checks UDP socket for new data
Arguments:
	none
Return:
	none
================================================*/
bool UDPReceiver::checkUDP()
{
	int bytesRecievedCount = 0;

	try
	{
		bytesRecievedCount = recvfrom(ourSocket, buffer, BUFSIZE, MSG_DONTWAIT, (struct sockaddr *)&remoteAddress, &addressLength);
	}
	catch (const int e)
	{
		bytesRecievedCount = 0;
	}

	if (bytesRecievedCount > 0) {
		buffer[bytesRecievedCount] = '\0';
		std::string bufferString = buffer;

		std::vector<std::string> dataPointsStrings = Utility::SplitString(bufferString, ',');

		std::vector<std::vector<float>> dataPoints;

		std::vector<float> currentDataPoint;

		// Convert to float and sort data points by size from smallest to greatest distance
		for (unsigned int i = 0; i < dataPointsStrings.size(); i++)
		{
			currentDataPoint = Utility::StrVectorToFloatVector(Utility::SplitString(dataPointsStrings[i], ' '));

			// If data point is the right length, add it to the right position in the dataPoints vector (sorted by percent match)
			if (currentDataPoint.size() == UDP::DataCount)
				for (unsigned int j = 0; j <= dataPoints.size(); j++)
					if (j >= dataPoints.size() || currentDataPoint[UDP::Index::PercentMatch] > dataPoints[j][UDP::Index::PercentMatch])
					{
						dataPoints.insert(dataPoints.begin() + j, currentDataPoint);
						j = dataPoints.size() + 1;
					}
		}

		if (dataPoints.size() > 1)
		{
			// If one target is a much worse match than the other, ignore the data
			if (dataPoints[1][UDP::Index::PercentMatch] / dataPoints[0][UDP::Index::PercentMatch] > 0.75)
			{
				// Average two best matches
				for (unsigned int i = 0; i < UDP::DataCount; i++)
					newestUDPData[i] = (dataPoints[0][i] + dataPoints[1][i]) / 2;
				UDPAgeTimer.Reset();
				isRealData = true;

				return true;
			}
		}
	}

	return false;
}

void UDPReceiver::clearUDPSocket()
{
	int packetsCleared = 0;
	int bytesRecievedCount = 1;

	while (bytesRecievedCount > 0 && packetsCleared < UDP::MaxPacketsFlush)
	{
		try
		{
			bytesRecievedCount = recvfrom(ourSocket, buffer, BUFSIZE, MSG_DONTWAIT, (struct sockaddr *)&remoteAddress, &addressLength);
		}
		catch (const int e)
		{
			bytesRecievedCount = 0;
		}

		packetsCleared++;
	}
}
/*
	This is used during TeleopPeriodic
*/
void UDPReceiver::getTeleopUDPData(){
	UDPReceiver udpReceiver;

	/* ========== udpReceiver ========== */
	udpReceiver.checkUDP();
	udpReceiver.clearUDPSocket();

	float data[UDP::DataCount];
	udpReceiver.getUDPData(data);
}