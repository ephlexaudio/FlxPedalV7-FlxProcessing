/*
 * FlxMainInt.h
 *
 *  Created on: Jun 11, 2019
 *      Author: buildrooteclipse
 */

#ifndef FLXMAININT_H_
#define FLXMAININT_H_

#include <string>
#include <iostream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "structs.h"
#include "IpcStructs.h"

typedef struct  {
	bool footswitchStatus[10];
} footswitchStatusArray_t;


class FlxMainInt {
private:
	int fromFlxMainProcContFD;
	char fromFlxMainProcContIPCPath[50];
	_ipcComboStruct *fromFlxMainProcContMemory;
	int openProcessingIPC();
	int closeProcessingIPC();
#if(1)
	int fromFlxMainUtilityFD;
	char fromFlxMainUtilityIPCPath[50];
	_ipcProcessUtilityStruct *fromFlxMainUtilityMemory;
	int openUtilityIPC();
	int closeUtilityIPC();
#endif

public:
	FlxMainInt();
	virtual ~FlxMainInt();

	bool loadComboRqst();
	void comboLoaded();
	bool isComboLoaded();
	ComboStruct getComboStruct();
	_ipcComboStruct *getIpcComboStructPtr();
	bool loadProcessUtilityRqst();
	void processUtilityLoaded();
	bool isProcessUtilityLoaded();
	ProcessUtilityStruct getProcessUtilityStruct();
	_ipcProcessUtilityStruct *getIpcProcessUtilityStructPtr();

	footswitchStatusArray_t updateFootswitchStatusArray();
	string getFlxMainComboName();



};



#endif /* FLXMAININT_H_ */
