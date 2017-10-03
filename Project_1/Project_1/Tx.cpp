#include <iostream>
#include <math.h>
#include "Tx.h"
#include "Constants.h"

using namespace std;


Tx::Tx(int backOff, int lamda)
{
	this->val_BO = backOff;
	this->lamda = lamda;

}

Tx::~Tx()
{
}

void generateTraffic(vector<double> & v, int lamda)
{
	double sum = 0;
	double temp = 0;
	double tot = 0;
	v.push_back(0);
	for (int i = 1; i < 10 * lamda; ++i)
	{
		sum = 1 / (10 * lamda) + sum;
		temp = (-1 / lamda) * log(1 - sum);
		temp = temp * TIME_BLOCK;
		tot += temp;
		v.push_back(tot);	//time is in blocks!!
	}
}

int recieveTime(int time)
{

}

string sendMessage()
{

}

void backoff()
{

}

int transmit(int frames)
{

}

int generateTraffic()
{

}

void collision(int col_num)
{

}