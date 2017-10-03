#pragma once

#include <sstream>
#include <iomanip>

using namespace std;

double roundTot(double val)
{
	stringstream tmp;
	tmp << setprecision(1) << fixed << val;
	double new_val = stod(tmp.str());
	tmp.str(string());

	return new_val;
}

void generateTraffic(int lamda, vector<double> & v)
{
	double sum = 0;
	double temp = 0;
	double tot = 0;
	v.push_back(0);
	for (int i = 1; i < 10 * lamda; ++i)
	{
		sum = 1 / (10 * lamda) + sum;
		temp = (-1 / lamda) * log(1 - sum) * TIME_BLOCK;
		tot += temp;

		v.push_back(roundTot(tot));	//time is in blocks!!
	}
}