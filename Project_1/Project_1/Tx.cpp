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
	this->CTS_val = CTS_ORIGINAL;
	this->RTS_val = RTS_ORIGINAL;
	this->DIFS_val = DIFS_ORIGINAL;
	this->SIFS_val = SIFS_ORIGINAL;
	this->xfer_Time = DATA_FRAME_SIZE;

	this->numAck = 0;
	this->numCollisions = 0;

	setBackOff();
	setCollisionTime();
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
			if (!Transmitting)
			{


				if (DIFS_val != 0)
				{
					DIFS_val -= TIME_INC;
					return stat;
				}
				else
					stat = BACKOFF;
				break;
			}
			stat = FREEZE;
			break;
		case BACKOFF:
			if (!Transmitting)
			{
				if (backOff_val != 0)
				{
					backOff_val -= TIME_INC;
					return stat;
				}
				else
					stat = RTS;
			}
			else
				stat = FREEZE;
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
				Transmitting = false;
				Queue.pop();
				resetVariables(true);

				++numAck;
				stat = QUE;
			}
			break;
		case FREEZE:
			if (!Transmitting)
			{
				DIFS_val = DIFS_ORIGINAL;
				stat = DIFS;
			}
			else
				return stat;
			break;
		case COLLISION:
			if (this->collisionTime > TIME_INC)
			{
				collisionTime -= TIME_INC;
				return stat;
			}
			else
			{
				resetVariables(false);
				stat = DIFS;
			}
			break;
		case RTS:
			if (RTS_val != 0)
			{
				RTS_val -= TIME_INC;
				return stat;
			}
			else
				stat = CTS;
			break;
		case CTS:
			if (CTS_val != 0)
			{
				CTS_val -= TIME_INC;
				return stat;
			}
			else
			{
				sendMessage();
				stat = SENDING;
			}
			break;
		}
	}
	//updateTime(t);

	return stat;
}

void Tx::sendMessage()
{
	this->xfer_Time = DATA_FRAME_SIZE + SIFS + ACK;	// slots
}

void Tx::setBackOff()
{
	this->backOff_val = rand() % (CWo - 1);
}

void Tx::collision(double k)
{
	if (k>10)
		k = 10;
		
	int CW = ((int)pow(2.0, k) * CWo - 1);

	if (CW > CWmax)
		CW = CWmax;

	this->backOff_val = rand() % CW;
	DIFS_val = DIFS_ORIGINAL;	// Reset variables
	stat = COLLISION;
}

void Tx::setCollisionTime()
{
	this->collisionTime = SIFS_ORIGINAL + DATA_FRAME_SIZE + ACK_ORIGINAL + CTS_ORIGINAL + this->RTS_val;
}

void Tx::resetVariables(bool BO)
{
	RTS_val = RTS_ORIGINAL;		// Reset variables
	CTS_val = CTS_ORIGINAL;
	DIFS_val = DIFS_ORIGINAL;	
	SIFS_val = SIFS_ORIGINAL;
	xfer_Time = DATA_FRAME_SIZE;
	ACK_val = ACK_ORIGINAL;
	if (BO)
		setBackOff();
	setCollisionTime();
}

int Tx::getNumACK()
{
	return this->numAck;
}

void Tx::setState(int state)
{
	this->stat = state;
}

void Tx::printVector()    //Debugging to verify Traffic Generator
{
	for (int i = 0; i < Traffic.size(); ++i)
	{
		cout << i << " : " << Traffic[i] << endl;
	}
}

