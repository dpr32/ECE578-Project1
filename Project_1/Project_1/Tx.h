#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Tx
{
private:
	int DIFS_VAL;
	int lamda;
	int stat;
	int numCollisions;
	int ACK_VAL;

	queue<double> Queue;
	vector<double> Traffic;

	int SIFS_VAL;
	int	 backOff_VAL;
	int xfer_Time;
	int realTime;
	int nextTime;

	

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