/*
 * main.cpp
 *
 *  Created on: Jun 8, 2019
 *      Author: buildrooteclipse
 */

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <thread>
#include <vector>
#include <algorithm>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>


#include "utilityFunctions.h"
#include "Processing.h"
#include "GPIOClass.h"
#include "config.h"
#include "FlxMainInt.h"
using namespace std;


Processing *processing;

static void signal_handler(int sig)
{

	 std::cout << "signal received: " << sig <<", FlxProcessing exiting ..." << std::endl;

	signal(sig, SIG_DFL);
	kill(getpid(),sig);

}

void createComboProcessor(ProcessUtilityStruct procUtilStruct, int bufferSize);
int startComboProcessing();
void stopComboProcessing();


int main(int argc, char *argv[])
{
	FlxMainInt flxMain;

	/*****************START: Start up and init of pedal *******************/
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGTRAP, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGBUS, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGALRM, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGSTKFLT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGXCPU, signal_handler);
	signal(SIGXFSZ, signal_handler);
	signal(SIGVTALRM, signal_handler);
	signal(SIGPROF, signal_handler);
	cpu_set_t proc_set;
	CPU_ZERO(&proc_set);
	CPU_SET(2,&proc_set);
	sched_setaffinity(getpid(),sizeof(proc_set),&proc_set);
	cout << "FlxProcessing PID: " << getpid() << endl;
	ComboStruct comboStruct;
	ProcessUtilityStruct procUtilStruct;
	footswitchStatusArray_t footswitchStatusArray;
	bool exit = false;

	//create client and start combo processing (audioCallback)
	createComboProcessor(flxMain.getProcessUtilityStruct(), 256);
	startComboProcessing();
	usleep(1000);
	//attach to IPC from OfxMain

	processing->setIpcComboStructPtr(flxMain.getIpcComboStructPtr());
	processing->setIpcProcessUtilityPtr(flxMain.getIpcProcessUtilityStructPtr());

	//main loop
	for(;;)
	{
		if(flxMain.loadComboRqst())
		{
			cout << "loading new combo." << endl;
			comboStruct = flxMain.getComboStruct();
			processing->disableProcessing();
			usleep(10000);
			processing->unloadCombo();
			usleep(500000);
			processing->loadCombo(comboStruct);
			usleep(10000);
			processing->enableProcessing();
			cout << "new combo loaded." << endl;
			flxMain.comboLoaded();
		}
		if(flxMain.loadProcessUtilityRqst())
		{

			cout << "loading utilities." << endl;
			procUtilStruct = flxMain.getProcessUtilityStruct();
			processing->loadProcessUtility(procUtilStruct);
			cout << "utilities loaded." << endl;
			flxMain.processUtilityLoaded();
		}

		usleep(30000);
		processing->readFootswitches();
	}
	stopComboProcessing();

	return 0;
}



#define dbg 1
void createComboProcessor(ProcessUtilityStruct procUtilStruct, int bufferSize)
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING:  createComboProcessor" << endl;
#endif
	 try
	 {
		processing = new Processing(procUtilStruct, bufferSize);// initial ports from constructor created here.
		// bypass processing
		processing->disableProcessing();
	 }
	 catch(exception &e)
	 {
		 cout << "exception in createComboProcessor: " << e.what() << endl;
	 }

#if(dbg >= 1)
	 cout << "***** EXITING:  createComboProcessor" << endl;
#endif

}



#define dbg 1
int startComboProcessing() // start clients and connect them
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING: startComboProcessing" << endl;
#endif

	 try
	 {
			processing->start();	// activate the client
		#if(dbg >= 1)
			 cout << "process started." << endl;
		#endif
			// reporting some client info
		#if(dbg >= 1)
			 //cout << "my name: " << this->processing->getName() << endl;
		#endif

			// test to see if it is real time
			if(processing->isRealTime())
			{
		#if(dbg >= 1)
				 cout << "is realtime " << endl;
			}
			else
			{
				 cout << "is not realtime " << endl;
		#endif
			}

			//connect our ports to physical ports


			processing->connectFromPhysical(0,0);	// connects this client in port 0 to physical source port 0
			processing->connectFromPhysical(1,1);	// connects this client in port 1 to physical source port 1
			processing->connectToPhysical(0,0);		// connects this client out port 0 to physical destination port 0
			processing->connectToPhysical(1,1);		// connects this client out port 1 to physical destination port 1

	 }
	 catch(exception &e)
	 {
		 cout << "exception in startComboProcessing: " << e.what() << endl;
	 }

#if(dbg >= 1)
	 cout << "***** EXITING: startComboProcessing: " << status << endl;
#endif

	return status;

}


#define dbg 1
void stopComboProcessing() // stop clients and disconnect them
{
#if(dbg >= 1)
	 cout << "***** ENTERING: stopComboProcessing" << endl;
#endif

	processing->disconnectInPort(0);	// Disconnecting ports.
	processing->disconnectOutPort(1);
	processing->stop();
	processing->close();	// stop client.
	delete processing;	// always clean up after yourself.


#if(dbg >= 1)
	 cout << "***** EXITING: stopComboProcessing: " <<  endl;
#endif

}
