#include <iostream>
#include <math.h>

#include "Constants.h"
#include "Main.h"
#include "Tx.h"

using namespace std;

Tx::Tx(int lamda)    /*Constructor*/
{
	this->DIFS_VAL = DIFS_ORIGINAL;
	this->SIFS_VAL = SIFS_ORIGINAL;
	this->realTime = 0;
	this->nextTime = 0;
	this->xfer_Time = DATA_FRAME_SIZE;
	this->numCollisions = 0;
	this->stat = QUE;
	this->ACK_VAL = ACK_ORIGINAL;
	this->lamda = lamda;


	setBackOff();
	generateTraffic(lamda, this->Traffic);
}

Tx::~Tx()    /*Deconstructor*/
{
}

int Tx::recieveTime(double t)
{
	if(t == this ->Traffic[0])
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


				if (DIFS_VAL != 0)
				{
					DIFS_VAL -= TIME_INC;
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
				if (backOff_VAL != 0)
				{
					backOff_VAL -= TIME_INC;
					return stat;
				}
				else
				{
					sendMessage();
					stat = SENDING;
				}
			}
			else
				return stat;

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
			if (SIFS_VAL != 0)
			{
				SIFS_VAL -= TIME_INC;
				return stat;
			}
			else
				stat = ACK;
			break;
		case ACK:
			if (ACK_VAL != 0)
			{
				ACK_VAL -= TIME_INC;
				return stat;
			}
			else
			{
				Transmitting = false;
				Queue.pop();

				DIFS_VAL = DIFS_ORIGINAL;	// Reset variables
				SIFS_VAL = SIFS_ORIGINAL;
				xfer_Time = DATA_FRAME_SIZE;
				ACK_VAL = ACK_ORIGINAL;
				setBackOff();

				stat = QUE;
			}
			break;
		case FREEZE:
			if (!Transmitting)
			{
				stat = DIFS;
			}
			else
				return stat;
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
	

	this->backOff_VAL = rand() % (CWo - 1);
}

int Tx::transmit(int frames)
{
	return 0;
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

	this->backOff_VAL = rand() % CW;
	DIFS_VAL = DIFS_ORIGINAL;	// Reset variables
	stat = DIFS;



}

void Tx::updateTime(double t)
{
	this->realTime = t;
}

void Tx::printVector()    //Debugging to verify Traffic Generator
{
	for (int i = 0; i < Traffic.size(); ++i)
	{
		cout << i << " : " << Traffic[i] << endl;
	}
}

