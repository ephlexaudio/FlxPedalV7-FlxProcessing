/*
 * FlxMainInt.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: buildrooteclipse
 */

#include "FlxMainInt.h"

using namespace std;







FlxMainInt::FlxMainInt() {
	openProcessingIPC();
	openUtilityIPC();

}

FlxMainInt::~FlxMainInt() {
	closeProcessingIPC();
	closeUtilityIPC();
}



#define dbg 1
int FlxMainInt::openProcessingIPC()
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::openProcessingIPC" << endl;
#endif

		try
		{
			sprintf(this->fromFlxMainProcContIPCPath,"/ipc_toFlxProcessingComboInt");
			this->fromFlxMainProcContFD = shm_open(this->fromFlxMainProcContIPCPath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			if(this->fromFlxMainProcContFD == -1)
			{
				printf("toProdFD open failed.\n");
			}
			else
			{
				this->fromFlxMainProcContMemory = (_ipcComboStruct *)mmap (NULL, sizeof(_ipcComboStruct), PROT_WRITE | PROT_READ,
						MAP_SHARED, this->fromFlxMainProcContFD, 0);
			}



			close(this->fromFlxMainProcContFD);
		}
		catch(exception &e)
		{
			cout << "exception in FlxMainInt::openProcessingIPC: " << e.what();
			status = -1;
		}

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::openProcessingIPC: " << status << endl;
#endif
	return status;
}

int FlxMainInt::closeProcessingIPC()
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::closeProcessingIPC" << endl;
#endif

	if(munmap(this->fromFlxMainProcContMemory, this->fromFlxMainProcContFD) == -1) status = -1;

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::closeProcessingIPC: " << status << endl;
#endif
	return status;
}

#if(1)
int FlxMainInt::openUtilityIPC()
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::openUtilityIPC" << endl;
#endif

		try
		{
			sprintf(this->fromFlxMainUtilityIPCPath,"/ipc_toFlxProcessingUtilInt");
			this->fromFlxMainUtilityFD = shm_open(this->fromFlxMainUtilityIPCPath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			if(this->fromFlxMainUtilityFD == -1)
			{
				printf("toProdFD open failed.\n");
			}
			else
			{
				this->fromFlxMainUtilityMemory = (_ipcProcessUtilityStruct *)mmap (NULL, sizeof(_ipcProcessUtilityStruct), PROT_WRITE | PROT_READ,
						MAP_SHARED, this->fromFlxMainUtilityFD, 0);
			}



			close(this->fromFlxMainUtilityFD);
		}
		catch(exception &e)
		{
			cout << "exception in FlxMainInt::openUtilityIPC: " << e.what();
			status = -1;
		}

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::openUtilityIPC: " << status << endl;
#endif
	return status;
}


int FlxMainInt::closeUtilityIPC()
{
	int status = 0;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::closeUtilityIPC" << endl;
#endif

	if(munmap(this->fromFlxMainUtilityMemory, this->fromFlxMainUtilityFD) == -1) status = -1;

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::closeUtilityIPC: " << status << endl;
#endif
	return status;

}
#endif



#define dbg 0
bool FlxMainInt::loadComboRqst()
{

#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::loadComboRqst" << endl;
#endif


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::loadComboRqst" << endl;
#endif
	return this->fromFlxMainProcContMemory->loadCombo;
}

#define dbg 0
void FlxMainInt::comboLoaded()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::comboLoaded" << endl;
#endif
		this->fromFlxMainProcContMemory->comboLoaded = true;


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::comboLoaded" << endl;
#endif
}


#define dbg 0
bool FlxMainInt::isComboLoaded()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::isComboLoaded" << endl;
#endif


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::isComboLoaded" << endl;
#endif
	 return this->fromFlxMainProcContMemory->comboLoaded;

}


#define dbg 0
ComboStruct FlxMainInt::getComboStruct()
{
	ComboStruct tempCombo;
	ComboStruct nullCombo;
	int status = 0;
#if(dbg >= 1)
	 cout << "*****ENTERING FlxMainInt::getComboStruct" << endl;
	 cout << "comboName: " << this->fromFlxMainProcContMemory->name << endl;
#endif

	try
	{
		tempCombo.controlVoltageEnabled = false;
		tempCombo.processCount = this->fromFlxMainProcContMemory->processCount;
		tempCombo.controlCount = this->fromFlxMainProcContMemory->controlCount;
		tempCombo.processSignalBufferCount = this->fromFlxMainProcContMemory->processSignalBufferCount;
		tempCombo.processParamControlBufferCount =
				this->fromFlxMainProcContMemory->processParamControlBufferCount;

		tempCombo.name = string(this->fromFlxMainProcContMemory->name);
#if(dbg >= 2)
		 cout << tempCombo.name << ":" << tempCombo.processCount << ":" << tempCombo.controlCount << ":" << tempCombo.processSignalBufferCount << endl;
#endif
		// set Processes
		int i = 0;
		int j = 0;
		for(i = 0; i < this->fromFlxMainProcContMemory->processCount; i++)
		{
			tempCombo.processSequenceData[i].processName =
					string(this->fromFlxMainProcContMemory->processSequenceData[i].processName);
			tempCombo.processSequenceData[i].processTypeInt =
					this->fromFlxMainProcContMemory->processSequenceData[i].processTypeInt;

			tempCombo.processSequenceData[i].footswitchNumber =
					this->fromFlxMainProcContMemory->processSequenceData[i].footswitchNumber-1;
			tempCombo.processSequenceData[i].processSequenceIndex =
					this->fromFlxMainProcContMemory->processSequenceData[i].processSequenceIndex;
#if(dbg >= 2)
			 cout << "tempCombo.processSequenceData[" << i << "].processName: " << tempCombo.processSequenceData[i].processName << endl;
			 cout << "tempCombo.processSequenceData[" << i << "].procType: " << tempCombo.processSequenceData[i].processTypeInt << endl;
			 cout << "tempCombo.processSequenceData[" << i << "].footswitchNumber: " << tempCombo.processSequenceData[i].footswitchNumber << endl;
#endif
			//***************** Get input count and store values **************
			tempCombo.processSequenceData[i].processInputCount =
					this->fromFlxMainProcContMemory->processSequenceData[i].processInputCount;
#if(dbg >= 2)
			 cout << "tempCombo.processSequenceData[" << i << "].processInputCount: " << tempCombo.processSequenceData[i].processInputCount << endl;
#endif
			for(j = 0; j < this->fromFlxMainProcContMemory->processSequenceData[i].processInputCount; j++)
			{
				tempCombo.processSequenceData[i].inputConnectedBufferIndexArray[j] =
						this->fromFlxMainProcContMemory->processSequenceData[i].inputConnectedBufferIndexArray[j];

#if(dbg >= 2)
				 cout << "tempCombo.processSequenceData[" << i << "].inputConnectedBufferIndexArray[" << j << "]: " << tempCombo.processSequenceData[i].inputConnectedBufferIndexArray[j] << endl;
#endif
			}

			//***************** Get output count and store values  **************
			tempCombo.processSequenceData[i].processOutputCount =
					this->fromFlxMainProcContMemory->processSequenceData[i].processOutputCount;
#if(dbg >= 2)
			 cout << "tempCombo.processSequenceData[" << i << "].processOutputCount: " << tempCombo.processSequenceData[i].processOutputCount << endl;
#endif
			for(j = 0; j < this->fromFlxMainProcContMemory->processSequenceData[i].processOutputCount; j++)
			{

				tempCombo.processSequenceData[i].outputConnectedBufferIndexArray[j] =
						this->fromFlxMainProcContMemory->processSequenceData[i].outputConnectedBufferIndexArray[j];
#if(dbg >= 2)
				 cout << "tempCombo.processSequenceData[" << i << "].outputConnectedBufferIndexArray[" << j << "]: " << tempCombo.processSequenceData[i].outputConnectedBufferIndexArray[j] << endl;
#endif
			}

			//***************** Get parameter count and store values **************
			tempCombo.processSequenceData[i].parameterCount =
					this->fromFlxMainProcContMemory->processSequenceData[i].parameterCount;
			for(j = 0; j < this->fromFlxMainProcContMemory->processSequenceData[i].parameterCount; j++)
			{
				tempCombo.processSequenceData[i].parameterArray[j].internalIndexValue =
						this->fromFlxMainProcContMemory->processSequenceData[i].parameterArray[j].internalIndexValue;
				tempCombo.processSequenceData[i].parameterArray[j].paramContBufferIndex =
						this->fromFlxMainProcContMemory->processSequenceData[i].parameterArray[j].paramContBufferIndex;
				tempCombo.processSequenceData[i].parameterArray[j].parameterName =
						string(this->fromFlxMainProcContMemory->processSequenceData[i].parameterArray[j].parameterName);
				tempCombo.processSequenceData[i].parameterArray[j].controlConnected =
						this->fromFlxMainProcContMemory->processSequenceData[i].parameterArray[j].controlConnected;
#if(dbg >= 2)
				 cout << "tempCombo.processSequenceData[" << i << "].parameterArray[" << j << "]->";
				 cout << " internalIndexValue: "<< tempCombo.processSequenceData[i].parameterArray[j].internalIndexValue;
				 cout << "\tparamContBufferIndex: " << tempCombo.processSequenceData[i].parameterArray[j].paramContBufferIndex << endl;
#endif
			}

			for(; j < 10; j++)
			{
				tempCombo.processSequenceData[i].parameterArray[j].internalIndexValue = 0;
				tempCombo.processSequenceData[i].parameterArray[j].controlConnected = false;
			}
			tempCombo.processSequenceData[i].bufferSize = 256;
			tempCombo.processSequenceData[i].inputCouplingMode = 1;
			tempCombo.processSequenceData[i].antiAliasingNumber = 1;
			tempCombo.processSequenceData[i].waveshaperMode = 0;
		}

		// set Controls
		for(i = 0; i < this->fromFlxMainProcContMemory->controlCount; i++)
		{
			tempCombo.controlSequenceData[i].controlName =
					string(this->fromFlxMainProcContMemory->controlSequenceData[i].controlName);
			tempCombo.controlSequenceData[i].conType =
					this->fromFlxMainProcContMemory->controlSequenceData[i].controlTypeInt;
#if(dbg >= 2)
			 cout << "tempCombo.controlSequenceData[" << i << "].name: " << tempCombo.controlSequenceData[i].controlName << endl;
			 cout << "tempCombo.controlSequenceData[" << i << "].conType: " << tempCombo.controlSequenceData[i].conType << endl;
#endif

			tempCombo.controlSequenceData[i].outputConnectionCount =
					this->fromFlxMainProcContMemory->controlSequenceData[i].outputConnectionCount;

			for(j = 0; j < tempCombo.controlSequenceData[i].outputConnectionCount; j++)
			{
				tempCombo.controlSequenceData[i].outputToParamControlBufferIndex[j] =
						this->fromFlxMainProcContMemory->controlSequenceData[i].outputToParamControlBufferIndex[j];
#if(dbg >= 2)
				 cout << "tempCombo.controlSequenceData[" << i << "].outputToParamControlBufferIndex: " << tempCombo.controlSequenceData[i].outputToParamControlBufferIndex[j] << endl;
#endif
			}

			tempCombo.controlSequenceData[i].outputInvConnectionCount =
					this->fromFlxMainProcContMemory->controlSequenceData[i].outputInvConnectionCount;

			for(j = 0; j < tempCombo.controlSequenceData[i].outputInvConnectionCount; j++)
			{
				tempCombo.controlSequenceData[i].outputInvToParamControlBufferIndex[j] =
						this->fromFlxMainProcContMemory->controlSequenceData[i].outputInvToParamControlBufferIndex[j];
#if(dbg >= 2)
				 cout << "tempCombo.controlSequenceData[" << i << "].outputInvToParamControlBufferIndex: " << tempCombo.controlSequenceData[i].outputInvToParamControlBufferIndex[j] << endl;
#endif
			}


			tempCombo.controlSequenceData[i].parameterCount =
					this->fromFlxMainProcContMemory->controlSequenceData[i].parameterCount;

			for(j = 0; j < tempCombo.controlSequenceData[i].parameterCount; j++)
			{
				tempCombo.controlSequenceData[i].parameterArray[j].parameterName =
						string(this->fromFlxMainProcContMemory->controlSequenceData[i].parameterArray[j].parameterName);
				tempCombo.controlSequenceData[i].parameterArray[j].value =
						this->fromFlxMainProcContMemory->controlSequenceData[i].parameterArray[j].value;
				tempCombo.controlSequenceData[i].parameterArray[j].cvEnabled =
						this->fromFlxMainProcContMemory->controlSequenceData[i].parameterArray[j].cvEnabled;
				if(tempCombo.controlSequenceData[i].parameterArray[j].cvEnabled == true)
				{
					tempCombo.controlVoltageEnabled = true; // used to set analog input mode to DC.
				}
#if(dbg >= 2)

				{
					cout << "tempCombo.controlSequenceData[" << i << "].parameterArray[" << j << "].value: ";
					cout << tempCombo.controlSequenceData[i].parameterArray[j].value;
					cout << "\t\ttempCombo.controlSequenceData[" << i << "].parameterArray[" << j << "].cvEnabled: ";
					cout << tempCombo.controlSequenceData[i].parameterArray[j].cvEnabled << endl;
				}
#endif
			}
			for(; j < 10; j++)
			{
				tempCombo.controlSequenceData[i].parameterArray[j].value = 0;
				tempCombo.controlSequenceData[i].parameterArray[j].cvEnabled = false;
			}
#if(dbg >= 2)
			 cout << "tempCombo.controlVoltageEnabled: " << tempCombo.controlVoltageEnabled << endl;
#endif
		}


		// set process signal buffering
		tempCombo.processSignalBufferCount =
				this->fromFlxMainProcContMemory->processSignalBufferCount;

		for(i = 0; i < tempCombo.processSignalBufferCount; i++)
		{
			tempCombo.processSignalBufferArray[i].srcProcess.objectName =
					string(this->fromFlxMainProcContMemory->processSignalBufferArray[i].
							srcProcessOutputConnector.parentObjectName);
			tempCombo.processSignalBufferArray[i].srcProcess.portName =
					string(this->fromFlxMainProcContMemory->processSignalBufferArray[i].
							srcProcessOutputConnector.connectorName);
			tempCombo.processSignalBufferArray[i].srcProcess.connectedBufferIndex =
					this->fromFlxMainProcContMemory->processSignalBufferArray[i].
					srcProcessOutputConnector.connectedBufferIndex;
			tempCombo.processSignalBufferArray[i].srcProcess.portIndex =
					this->fromFlxMainProcContMemory->processSignalBufferArray[i].
					srcProcessOutputConnector.connectorIndex;
		}

		// set parameterControl buffering
#if(dbg >= 2)
		 cout << "set processParamControl buffering: " << this->fromFlxMainProcContMemory->processParamControlBufferCount << endl;
#endif

		 tempCombo.processParamControlBufferCount = this->fromFlxMainProcContMemory->processParamControlBufferCount;

		for(i = 0; i < tempCombo.processParamControlBufferCount; i++)
		{
			tempCombo.processParamControlBufferArray[i].destProcessParameter.objectName =
					string(this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
							destProcessParameterConnector.parentObjectName);
			tempCombo.processParamControlBufferArray[i].destProcessParameter.portName =
					string(this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
							destProcessParameterConnector.connectorName);
			tempCombo.processParamControlBufferArray[i].destProcessParameter.connectedBufferIndex =
					this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
					destProcessParameterConnector.connectedBufferIndex;
			tempCombo.processParamControlBufferArray[i].srcControl.objectName =
					string(this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
							srcControlOutputConnector.parentObjectName);
			tempCombo.processParamControlBufferArray[i].srcControl.portName =
					string(this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
							srcControlOutputConnector.connectorName);
			tempCombo.processParamControlBufferArray[i].srcControl.connectedBufferIndex =
					this->fromFlxMainProcContMemory->processParamControlBufferArray[i].
					srcControlOutputConnector.connectedBufferIndex;
			tempCombo.processParamControlBufferArray[i].parameterValueIndex =
					this->fromFlxMainProcContMemory->processParamControlBufferArray[i].parameterValueIndex;


#if(dbg >= 3)
			if(tempCombo.processParamControlBufferArray[i].destProcessParameter.objectName.compare("empty") != 0)
			{
				cout << "destProcessParameter.objectName: " <<
								tempCombo.processParamControlBufferArray[i].destProcessParameter.objectName << endl;
				cout << "destProcessParameter.portName: " <<
								tempCombo.processParamControlBufferArray[i].destProcessParameter.portName << endl;
				cout << "destProcessParameter.connectedBufferIndex: " <<
								tempCombo.processParamControlBufferArray[i].destProcessParameter.connectedBufferIndex << endl;
				cout << "srcControl.objectName: " << tempCombo.processParamControlBufferArray[i].srcControl.objectName << endl;
				cout << "srcControl.portName: " << tempCombo.processParamControlBufferArray[i].srcControl.portName << endl;
				cout << "srcControl.connectedBufferIndex: " <<
								tempCombo.processParamControlBufferArray[i].srcControl.connectedBufferIndex << endl;
				cout << "parameterValueIndex: " << tempCombo.processParamControlBufferArray[i].parameterValueIndex << endl;
			}
#endif
		}




		tempCombo.inputSystemBufferIndex[0] = this->fromFlxMainProcContMemory->inputSystemBufferIndex[0];
#if(dbg >= 2)
		 cout << "tempCombo.inputSystemBufferIndex[0]: " << tempCombo.inputSystemBufferIndex[0] << endl;
#endif
		tempCombo.inputSystemBufferIndex[1] = this->fromFlxMainProcContMemory->inputSystemBufferIndex[1];
#if(dbg >= 2)
		 cout << "tempCombo.inputSystemBufferIndex[1]: " << tempCombo.inputSystemBufferIndex[1] << endl;
#endif
		tempCombo.outputSystemBufferIndex[0] = this->fromFlxMainProcContMemory->outputSystemBufferIndex[0];
#if(dbg >= 2)
		 cout << "tempCombo.outputSystemBufferIndex[0]: " << tempCombo.outputSystemBufferIndex[0] << endl;
#endif
		tempCombo.outputSystemBufferIndex[1] = this->fromFlxMainProcContMemory->outputSystemBufferIndex[1];
#if(dbg >= 2)
		 cout << "tempCombo.outputSystemBufferIndex[1]: " << tempCombo.outputSystemBufferIndex[1] << endl;
#endif
	}
	catch(exception &e)
	{
		 cout << "exception in FlxMainInt::getIpcComboStruct: " << e.what() << endl;
		status = -1;

	}
#if(dbg >= 3)
	this->debugPrintParamContBufferListWithConnections();
	this->printIndexMappedComboData();
#endif
#if(dbg >= 1)
	 cout << "*****EXITING FlxMainInt::getComboStruct" << endl;
#endif

	if(status == 0) return tempCombo;
	else return nullCombo;
}




#define dbg 1
_ipcComboStruct *FlxMainInt::getIpcComboStructPtr()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::getIpcComboStructPtr" << endl;
#endif

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::getIpcComboStructPtr: " << this->fromFlxMainProcContMemory << endl;
#endif
	return this->fromFlxMainProcContMemory;

}

/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

#if(1)
#define dbg 0
bool FlxMainInt::loadProcessUtilityRqst()
{

#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::loadProcessUtilityRqst" << endl;
#endif


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::loadProcessUtilityRqst" << endl;
#endif
	return this->fromFlxMainUtilityMemory->loadProcessUtility;
}

#define dbg 0
void FlxMainInt::processUtilityLoaded()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::processUtilityLoaded" << endl;
#endif
		this->fromFlxMainUtilityMemory->processUtilityLoaded = true;


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::processUtilityLoaded" << endl;
#endif
}


#define dbg 0
bool FlxMainInt::isProcessUtilityLoaded()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::isProcessUtilityLoaded" << endl;
#endif


#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::isProcessUtilityLoaded" << endl;
#endif
	 return this->fromFlxMainUtilityMemory->processUtilityLoaded;

}



#define dbg 1
ProcessUtilityStruct FlxMainInt::getProcessUtilityStruct()
{
	ProcessUtilityStruct procUtil;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::getProcessUtilityStruct" << endl;
#endif

	procUtil.envTrigger.highThres  = this->fromFlxMainUtilityMemory->envTrigger.highThres;
	procUtil.envTrigger.lowThres  = this->fromFlxMainUtilityMemory->envTrigger.lowThres;

	procUtil.noiseGate.closeThres = this->fromFlxMainUtilityMemory->noiseGate.closeThres;
	procUtil.noiseGate.gain = this->fromFlxMainUtilityMemory->noiseGate.gain;
	procUtil.noiseGate.openThres = this->fromFlxMainUtilityMemory->noiseGate.openThres;

	procUtil.process.antiAliasingNumber = this->fromFlxMainUtilityMemory->process.antiAliasingNumber;
	procUtil.process.bufferSize = this->fromFlxMainUtilityMemory->process.bufferSize;
	procUtil.process.inputCouplingMode = this->fromFlxMainUtilityMemory->process.inputCouplingMode;
	procUtil.process.waveshaperMode = this->fromFlxMainUtilityMemory->process.waveshaperMode;

	procUtil.trigger.highThres = this->fromFlxMainUtilityMemory->trigger.highThres;
	procUtil.trigger.lowThres = this->fromFlxMainUtilityMemory->trigger.lowThres;
#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::getProcessUtilityStruct" << endl;
#endif

	return procUtil;
}

_ipcProcessUtilityStruct *FlxMainInt::getIpcProcessUtilityStructPtr()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::getIpcProcessUtilityStructPtr" << endl;
#endif

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::getIpcProcessUtilityStructPtr: " << this->fromFlxMainUtilityMemory << endl;
#endif
	return this->fromFlxMainUtilityMemory;
}


#endif



/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/



#define dbg 0
footswitchStatusArray_t FlxMainInt::updateFootswitchStatusArray(void)
{
	footswitchStatusArray_t tempFootswitchStatusArray;
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::updateFootswitchStatusArray" << endl;
#endif

	for(int i = 0; i < 10; i++)
	{
		tempFootswitchStatusArray.footswitchStatus[i] =
				 ((this->fromFlxMainProcContMemory->footswitchStatus[i] == 1)?true:false);
#if(dbg >= 1)
	 cout << tempFootswitchStatusArray.footswitchStatus[i] << ",";
#endif
	}
#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::updateFootswitchStatusArray" << endl;
#endif

	return tempFootswitchStatusArray;
}


#define dbg 0
string FlxMainInt::getFlxMainComboName()
{
#if(dbg >= 1)
	 cout << "***** ENTERING: FlxMainInt::getFlxMainComboName" << endl;
#endif
		string name;
		name = this->fromFlxMainProcContMemory->name;

#if(dbg >= 1)
	 cout << "***** EXITING: FlxMainInt::getFlxMainComboName" << endl;
#endif
		return name;

}
