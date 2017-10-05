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
				{
					backOff_val -= TIME_INC;
					return stat;
				}
				else
				{
					sendMessage();
					stat = SENDING;
				}
			}
			else
				stat = FREEZE;
			break;
		case SENDING:
			{
				xfer_Time -= TIME_INC;
				return stat;
			}
			else
				stat = SIFS;
			break;
		case SIFS:
			{
				SIFS_val -= TIME_INC;
				return stat;
			}
			else
				stat = ACK;
			break;
		case ACK:
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
			if (this->collision_time > TIME_INC)
			{
				collision_time -= TIME_INC;
				return stat;
			}
			else
			{
				resetVariables(false);
				stat = DIFS;
			}
		}
	}
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
	{
		k = 10;
	}
		
	int CW = ((int)pow(2.0, k) * CWo - 1);

	if (CW > CWmax)
		CW = CWmax;

	this->backOff_val = rand() % CW;
	DIFS_val = DIFS_ORIGINAL;	// Reset variables
	stat = DIFS;
}

void Tx::setCollisionTime()
{
	this->collision_time = SIFS_ORIGINAL + DATA_FRAME_SIZE + ACK_ORIGINAL;
}

void Tx::resetVariables(bool BO)
{
	DIFS_val = DIFS_ORIGINAL;	// Reset variables
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

void Tx::printVector()    //Debugging to verify Traffic Generator
{
	for (int i = 0; i < Traffic.size(); ++i)
	{
		cout << i << " : " << Traffic[i] << endl;
	}
}

