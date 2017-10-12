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
	QUE,
	SIFS,
	BACKOFF,
	DIFS,
	SENDING,
	ACK,
	FREEZE,
	COLLISION
};