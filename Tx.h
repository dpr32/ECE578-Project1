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
	int consecutiveCollision;

	bool transCollision;

	queue<int> Queue;
	vector<int> Traffic;

	int numAck;

public:

	Tx(int lamda);	//Constructor
	~Tx();			//Deconstructor

	int getNumACK();
	int recieveTime(int t);

	void setBackOff();
	void sendMessage();
	void setCollisionTime();
	void setState(int state);
	int  getNumCollisions();
	bool getCollisionVariable();
	void resetVariables(bool BO);
	void collisionBackOff(double k);
	void setCollisionVariable(bool col);
	
	
	void printVector();	//Debugging
};