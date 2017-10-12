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
	int DIFS_val;
	int SIFS_val;
	int xfer_Time;
	int	backOff_val;
	int numCollisions;
	int collisionTime;
	int consecutiveCollision;

	bool transCollision;

	queue<double> Queue;
	vector<double> Traffic;

	int numAck;

public:

	Tx(int lamda);	//Constructor
	~Tx();			//Deconstructor

	int getNumACK();
	int recieveTime(double t);

	void setBackOff();
	void setMessageSize();
	int getCollisionNumber();
	void resetVariables(bool BO);
	void collisionBackOff(double col_num);
	
	void setCollisionVariable(bool col);

	void printVector();	//Debugging
};