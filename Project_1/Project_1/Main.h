#pragma once

#include <sstream>
#include <iomanip>
#include <vector>
#include <math.h>

#include "Constants.h"

using namespace std;

void generateTraffic(int lamda, vector<double> & v);

enum status {
	QUE,
	SIFS,
	BACKOFF,
	DIFS,
	SENDING,
	ACK
};