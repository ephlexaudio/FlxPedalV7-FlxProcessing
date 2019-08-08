/*
 * Controls.h
 *
 *  Created on: Mar 12, 2017
 *      Author: buildrooteclipse
 */

#ifndef CONTROLS_CONTROLS_H_
#define CONTROLS_CONTROLS_H_


#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <thread>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <json/json.h>

#include "../structs.h"





class Controls {
protected:
	ControlObjectData controlData;
	array<ProcessParameterControlBuffer,60> *processParamControlBufferArray;
	string name;
	int type;
	bool exitContThread;
	vector<int> outputToParamControlBufferIndex;
	vector<int> outputInvToParamControlBufferIndex;
	double output;
	double outputInv;
	int int_output;
	int int_outputInv;
	thread con_thrd;

public:
	Controls();
	Controls(ControlObjectData controlData);
	virtual ~Controls();

	string getName();
	int getType();
	int getControlParameterCount();
	void setParameter(int paramIndex, int valueIndex);
	int getParameter(int paramIndex);
	string getParameterName(int paramIndex);
	void setProcessParameterControlBufferArray(array<ProcessParameterControlBuffer,60> &procParamControlBufferArray);
	void exitThread();
	thread getContThread();
	virtual void load() = 0;
	virtual void run(int controlVoltageIndex, bool envTrigger) = 0;
	virtual void stop() = 0;
	virtual void contThread(int dummy) = 0;  // this combines load, run (exitable loop), and stop
};

class Normal : public Controls {
private:

public:
	Normal();
	Normal(ControlObjectData controlData);
	~Normal();

	void load();
	void run(int controlVoltageIndex, bool envTrigger);
	void stop();
	void contThread(int dummy);  // this combines load, run (exitable loop), and stop
};



class LFO : public Controls
{
private:
	int  cycleTimeValueIndex;
	double cyclePositionValue;
	int int_cyclePositionValue;
	double waveValue;

public:
	LFO();
	LFO(ControlObjectData controlData);
	~LFO();

	void load();
	void run(int controlVoltageIndex, bool envTrigger);
	void stop();
	void contThread(int dummy);  // this combines load, run (exitable loop), and stop
};

class EnvGen : public Controls
{
private:
	int envStage; //0:attack, 1:decay, 2:sustain, 3:release
	int stageTimeValue;
	double slewRate;
	bool envTrigger;
public:
	EnvGen();
	EnvGen(ControlObjectData controlData);
	~EnvGen();

	void load();

	void run(int controlVoltageIndex, bool envTrigger);
	void stop();
	void contThread(int dummy);  // this combines load, run (exitable loop), and stop
};




#endif /* CONTROLS_CONTROLS_H_ */
