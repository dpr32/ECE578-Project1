#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Tx
{
	int lamda;
	int DIFS = 2;
	int val_BO = 0;
	int numCollisions = 0;

	queue<double> Queue;
	vector<double> Traffic;

	double SIFS = 0.5;
	double realTime;
	double nextTime;

public:

	Tx(int backOff, int lamda); //Constructor
	~Tx(); //Deconstructor

	string sendMessage();
	void backoff();
	int transmit(int frames);
	int recieveTime(double t);
	void collision(int col_num);
	void updateTime(double t);
};

