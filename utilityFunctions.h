/*
 * utilityFunctions.h
 *
 *  Created on: Mar 20, 2016
 *      Author: mike
 */

#ifndef UTILITYFUNCTIONS_H_
#define UTILITYFUNCTIONS_H_

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <time.h>
#include <sys/time.h>
#include <json/json.h>
#include <linux/types.h>
#include <algorithm>

#include "structs.h"


	void startTimer(void);
	int stopTimer(const char *description);

	void pabort(const char *s);
	void clearBuffer(char *buffer, int length);


#endif /* UTILITYFUNCTIONS_H_ */
