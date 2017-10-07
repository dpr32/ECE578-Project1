#include <iostream>
#include <math.h>

#include "Constants.h"
#include "Main.h"
#include "Tx.h"

using namespace std;

Tx::Tx(int lamda)    /*Constructor*/
{
	this->stat = QUE;
	this->lamda = lamda;
	this->ACK_val = ACK_ORIGINAL;
	this->DIFS_val = DIFS_ORIGINAL;
	this->SIFS_val = SIFS_ORIGINAL;
	this->xfer_Time = DATA_FRAME_SIZE;
	this->consecutiveCollision = 0;


	this->numAck = 0;
	this->numCollisions = 0;

	setBackOff();
	setMessageSize();
	generateTraffic(lamda, this->Traffic);
}

Tx::~Tx()    /*Deconstructor*/
{
}

int Tx::recieveTime(double t)
{
	if(t == this->Traffic[0])
	{
		this->Queue.push(Traffic[0]);
		Traffic.erase(Traffic.begin());
	}

	while (1)
	{
		switch (stat)
		{
		case QUE:
			if (Queue.size() != 0)
				stat = DIFS;
			else
				return stat;
			break;
		case DIFS:
			if (DIFS_val != 0)
			{
				DIFS_val -= TIME_INC;
				return stat;
			}
			else
				stat = BACKOFF;
			break;
		case BACKOFF:
			if (backOff_val != 0)
			{
				backOff_val -= TIME_INC;
				return stat;
			}
			else
			{
				setMessageSize();
				stat = SENDING;
			}
			break;
		case SENDING:
			if (xfer_Time != 0)
			{
				xfer_Time -= TIME_INC;
				return stat;
			}
			else
				stat = SIFS;
			break;
		case SIFS:
			if (SIFS_val != 0)
			{
				SIFS_val -= TIME_INC;
				return stat;
			}
			else
				stat = ACK;
			break;
		case ACK:
			if (ACK_val != 0)
			{
				ACK_val -= TIME_INC;
				return stat;
			}
			else
			{
				if (transCollision)
				{
					++numCollisions;
					++consecutiveCollision;
					collisionBackOff(consecutiveCollision);
					resetVariables(false);
				}
				else
				{
					consecutiveCollision = 0;
					Queue.pop();
					resetVariables(true);
					++numAck;
				}
				setCollisionVariable(false);
				stat = QUE;
			}
			break;
		}
	}

	return stat;
}

void Tx::setMessageSize()
{
	this->xfer_Time = DATA_FRAME_SIZE;	// slots
}

void Tx::setBackOff()
{
	this->backOff_val = rand() % (CWo - 1);
}

void Tx::collisionBackOff(double k)
{
	if (k>10)
		k = 10;
		
	int CW = ((int)pow(2.0, k) * CWo - 1);

	if (CW > CWmax)
		CW = CWmax;

	this->backOff_val = rand() % CW;
}

void Tx::resetVariables(bool BO)
{
	DIFS_val = DIFS_ORIGINAL;	// Reset variables
	SIFS_val = SIFS_ORIGINAL;
	xfer_Time = DATA_FRAME_SIZE;
	ACK_val = ACK_ORIGINAL;
	if (BO)
		setBackOff();
}

int Tx::getNumACK()
{
	return this->numAck;
}

void Tx::setCollisionVariable(bool col)
{
	this->transCollision = col;
}

int Tx::getCollisionNumber()
{
	return this->numCollisions;
}

void Tx::printVector()    //Debugging to verify Traffic Generator
{
	for (int i = 0; i < Traffic.size(); ++i)
	{
		cout << i << " : " << Traffic[i] << endl;
	}
}

