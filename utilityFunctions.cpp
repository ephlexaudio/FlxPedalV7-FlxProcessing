/*
 * utilityFunctions.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: mike
 */


#include "utilityFunctions.h"
#include "config.h"

long startStamp;
long stopStamp;
struct timeval tv;

#define JSON_BUFFER_LENGTH 32000

using namespace std;


void startTimer(void)
{
	gettimeofday(&tv, NULL);
	startStamp = 1000000*tv.tv_sec+tv.tv_usec;
}

int stopTimer(const char *description)
{
	gettimeofday(&tv, NULL);
	stopStamp = 1000000*tv.tv_sec+tv.tv_usec;
	if(description != NULL)
	{
		 cout << "******" << description << "time: " << stopStamp - startStamp << endl;
	}

	return static_cast<int>(stopStamp - startStamp);
}



void clearBuffer(char *buffer, int length)
{
	uint16_t index;

	for(index = 0; index < length; index++)
	{
		buffer[index] = 0;
	}
}

void pabort(const char *s)
{
	perror(s);
}





