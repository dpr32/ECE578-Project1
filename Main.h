#pragma once

#include <sstream>
#include <iomanip>
#include <vector>
#include <math.h>

#include "Constants.h"

using namespace std;

extern bool Transmitting;

void generateTraffic(int lamda, vector<int> & v);
enum status {
	QUE,		//0
	SIFS,		//1
	BACKOFF,	//2
	DIFS,		//3
	SENDING,	//4
	ACK,		//5
	FREEZE,		//6
	RTS,		//7
	RTS_SIFS,	//8
	CTS,		//9
	CTS_SIFS	//10
};