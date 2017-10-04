#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Tx
{
private:
	int DIFS;
	int lamda;
	int numCollisions;

	queue<double> Queue;
	vector<double> Traffic;

	double SIFS;
	double backOff;
	double xfer_Time;
	double realTime;
	double nextTime;

	bool sending;

public:

	Tx(int lamda); //Constructor
	~Tx(); //Deconstructor

	void sendMessage();
	void setBackOff();
	int transmit(int frames);
	int recieveTime(double t);
	void collision(double col_num);
	void updateTime(double t);

	void printVector();	//Debugging
};