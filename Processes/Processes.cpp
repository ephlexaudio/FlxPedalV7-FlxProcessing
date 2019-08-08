/*
 * Processes.cpp
 *
 *  Created on: Jun 29, 2016
 *      Author: mike
 */


#include "Processes.h"
#include "../valueArrays.h"
#include "../structs.h"
#include "../config.h"



using namespace std;


#define dbg 0
Processes::Processes()
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::Processes(Default)" << endl;
#endif

	this->name = "Default";
	this->footswitchStatusArray = NULL;
	this->processSignalBufferArray = NULL;
	this->processParamControlBufferArray = NULL;
	this->exitProcThread = false;
#if(dbg >= 1)
	 cout << "EXITING Processes::Processes(Default)" << endl;
#endif

}

Processes::Processes(ProcessObjectData processData)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::Processes" << endl;
#endif

	this->processData = processData;
	this->name = processData.processName;
	this->footswitchStatusArray = NULL;
	this->processSignalBufferArray = NULL;
	this->processParamControlBufferArray = NULL;
	this->exitProcThread = false;
	this->startProcThread = false;
#if(dbg >= 1)
	 cout << "EXITING Processes::Processes" << this->name << ":" << this->processData.processName << endl;
#endif


}

Processes::~Processes()
{

}

#define dbg 0

string Processes::getName()
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::getName" << endl;
#endif

	 return this->name;

#if(dbg >= 1)
	 cout << "EXITING Processes::getName" << this->name << endl;
#endif
}

string Processes::getSymbol()
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::getSymbol" << endl;
#endif
	return this->processSymbol;
#if(dbg >= 1)
	 cout << "EXITING Processes::getSymbol" << this->processData.processName << endl;
#endif

}

int Processes::getProcessParameterCount()
{
	return this->processData.parameterCount;
}



#define dbg 1
void Processes::setIpcComboStructPtr(_ipcComboStruct *fromFlxMainProcContMemory)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::setIpcComboStructPtr" << endl;
#endif
	this->fromFlxMainProcContMemory = fromFlxMainProcContMemory;
#if(dbg >= 1)
	 cout << "EXITING Processes::setIpcComboStructPtr: " << this->fromFlxMainProcContMemory << endl;
#endif
}

#define dbg 1
void Processes::setIpcProcessUtilityStructPtr(_ipcProcessUtilityStruct *fromFlxMainUtilityMemory)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::setIpcProcessUtilityStructPtr" << endl;
#endif
	this->fromFlxMainUtilityMemory = fromFlxMainUtilityMemory;
#if(dbg >= 1)
	 cout << "EXITING Processes::setIpcProcessUtilityStructPtr: " << this->fromFlxMainUtilityMemory << endl;
#endif
}


#define dbg 0
void Processes::setProcessSignalBufferArray(array<ProcessSignalBuffer,60> &processSignalBufferArray)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::setProcessSignalBufferArray" << endl;
#endif
	this->processSignalBufferArray = &processSignalBufferArray;
#if(dbg >= 1)
	 cout << "EXITING Processes::setProcessSignalBufferArray: " << this->processSignalBufferArray << endl;
#endif
}


void Processes::setProcessParameterControlBufferArray(array<ProcessParameterControlBuffer,60> &procParamControlBufferArray)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::setProcessParameterControlBufferArray" << endl;
#endif
	this->processParamControlBufferArray = &procParamControlBufferArray;
#if(dbg >= 1)
	 cout << "EXITING Processes::setProcessParameterControlBufferArray: " << this->processParamControlBufferArray << endl;
#endif
}


void Processes::setFootswitchStatusArray(array<bool,10> &footswitchStatusArray)
{
#if(dbg >= 1)
	 cout << "ENTERING Processes::setFootswitchStatusArray" << endl;
#endif
	this->footswitchStatusArray = &footswitchStatusArray;
#if(dbg >= 1)
	 cout << "EXITING Processes::setFootswitchStatusArray: " << this->footswitchStatusArray << endl;
#endif
}


void Processes::setParameter(int paramIndex, int valueIndex)
{
	this->processData.parameterArray[paramIndex].internalIndexValue = valueIndex;
}


int Processes::clearProcBuffer(ProcessSignalBuffer *processSignalBuffer)
{
	int status = 0;
	#if(dbg >= 1)
	 cout << "ENTERING: clearProcBuffer" << endl;
#endif

	std::fill(std::begin(processSignalBuffer->buffer), std::end(processSignalBuffer->buffer), 0.0000);
#if(dbg >= 1)
	 cout << "EXITING: clearProcBuffer" << endl;
#endif

	return status;
}



