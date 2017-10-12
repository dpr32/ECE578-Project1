#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Tx
{
private:
	int stat;
	int lamda;
	int ACK_val;
	int RTS_val;
	int CTS_val;
	int DIFS_val;
	int SIFS_val;
	int xfer_Time;
	int	backOff_val;
	int numCollisions;
	int collisionTime;

	queue<int> Queue;
	vector<int> Traffic;

	int numAck;

public:

	Tx(int lamda);	//Constructor
	~Tx();			//Deconstructor

	int getNumACK();
	int recieveTime(double t);

	void setBackOff();
	void sendMessage();
	void setCollisionTime();
	void setState(int state);
	int Tx::getNumCollisions();
	void resetVariables(bool BO);
	void collision(double col_num);
	
	void printVector();	//Debugging
};