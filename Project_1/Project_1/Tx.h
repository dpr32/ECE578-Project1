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

	
	int numCollisions;
	int numAck;

public:

	Tx(int lamda);	//Constructor
	~Tx();			//Deconstructor

	int getNumACK();
	void setBackOff();
	void sendMessage();
	void setCollisionTime();
	int recieveTime(double t);
	void collision(double col_num);
	void resetVariables(bool BO);


	void printVector();	//Debugging
};