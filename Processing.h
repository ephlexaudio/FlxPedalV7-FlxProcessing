/*
 * Combo.h
 *
 *  Created on: Jun 28, 2016
 *      Author: mike
 */

#ifndef PROCESSING_H_
#define PROCESSING_H_


#include "Controls/Controls.h"
#include "Processes/Processes.h"
#include "GPIOClass.h"
#include "jackaudioio.h"
#include "structs.h"
#include "IpcStructs.h"
#include <thread>



class Processing: public JackCpp::AudioIO{
private:

	int bufferSize;
	bool inputsSwitched;
	double gateCloseThreshold;
	double gateOpenThreshold;
	double gateClosedGain;
	double gateGain;
	double triggerHighThreshold;
	double triggerLowThreshold;
	double noiseGateBuffer[1024];
	bool gateOpen;
	int gateStatus;
	int comboTime;
	bool envTrigger;
	int envTriggerStatus;
	double inPosPeak[2];
	double inNegPeak[2];
	double inMaxAmp[2];

	double inSignalLevel;
	double inPrevSignalLevel;
	double inSignalDeltaFilterOut;
	bool processingEnabled;
	string comboName;
	/************** Footswitch *********************/
	bool footSwitchPressed[2];
	GPIOClass footswitchLed[2];
	GPIOClass footswitchPin[2];
	array<bool,10> footswitchStatusArray;

	/***********************************************/
	_ipcComboStruct *fromFlxMainProcContMemory;
	_ipcProcessUtilityStruct *fromFlxMainUtilityMemory;
	/********* data structures from ComboStruct ***************/
	int processCount;
	int controlCount;
	int processSignalBufferCount;
	int processParamControlBufferCount;
	bool controlVoltageEnabled;
	Processes** processSequence;
	Controls** controlSequence;
	array<ProcessSignalBuffer,60> processSignalBufferArray;
	array<ProcessParameterControlBuffer,60> processParamControlBufferArray;
	map<string, ProcessIndexing>  processIndexMap;
	map<string, ControlIndexing>  controlIndexMap;
	vector<string> componentSymbolVector;
	vector<string> controlSymbolVector;
	bool comboLoaded;

	int inputSystemBufferIndex[2];
	int outputSystemBufferIndex[2];
	GPIOClass portConSwitch[3];
	GPIOClass audioOutputEnable;

	void triggerInputSignalFiltering();
	void noiseGate(double* bufferIn, double *bufferOut);
	void envelopeTrigger();
	void printProcessParameterControlBuffer();
	void loadComponentSymbolVector();
	void loadControlSymbolVector();

public:
	Processing();
	Processing(ProcessUtilityStruct procUtilStruct, int bufferSize);
	~Processing();

	void setIpcComboStructPtr(_ipcComboStruct *fromFlxMainProcContMemory);
	void setIpcProcessUtilityPtr(_ipcProcessUtilityStruct *fromFlxMainUtilityMemory);
	ProcessUtilityStruct getProcessUtilityStruct();
	string getComboName();
	void setComboName(string comboName);
	bool areInputsSwitched();
	int loadCombo(ComboStruct comboStruct);
	void unloadCombo();
	ComboStruct getComboStruct();
	/******audioCallback is where the processing and parameter control takes place ******/
	int audioCallback(jack_nframes_t nframes,
					// A vector of pointers to each input port.
					audioBufVector inBufs,
					// A vector of pointers to each output port.
					audioBufVector outBufs);

	void enableProcessing();
	void disableProcessing();
	int updateProcessParameter(string processName, string parameter, int parameterValue);
	int updateProcessParameters();
	void readFootswitches();
	void setProcessFootswitchStatus();
	int getProcessParameter(string processName, string parameter);

	int updateControlParameter(string controlName, string parameter, int parameterValue);
	int updateControlParameters();

	int getControlParameter(string controlName, string parameter);

	void setBufferSize(int bufferSize);
	int loadProcessUtility(ProcessUtilityStruct procUtilStruct);
	int updateProcessUtility();

};


#endif /* PROCESSING_H_ */
