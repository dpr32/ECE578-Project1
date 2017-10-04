#include <iostream>
#include <math.h>

#include "Constants.h"
#include "Main.h"
#include "Tx.h"

using namespace std;

Tx::Tx(int lamda)    /*Constructor*/
{
	this->DIFS = DIFS_DURRATION;
	this->SIFS = SIFS_DURRATION;
	this->realTime = 0;
	this->nextTime = 0;
	this->xfer_Time = 0;
	this->numCollisions = 0;

	this->lamda = lamda;
	this->sending = false;

	setBackOff();
	generateTraffic(lamda, this->Traffic);
}

Tx::~Tx()    /*Deconstructor*/
{
}

int Tx::recieveTime(double t)
{
	int stat;

	if (t == this->Traffic[0])
	{
		this->Queue.push(Traffic[0]);
		Traffic.pop_back();
	}

	if (sending)
	{
		this->xfer_Time -= TIME_INC;
		if (this->xfer_Time == 0)
		{
			sending = false;
			Transmitting = false;
			this->Queue.pop();

			this->DIFS = DIFS_DURRATION;		//Reset DIFS and BackOff
			setBackOff();

			stat = xfer_done;
		}
		stat = xmitting;
	}
	else if (Queue.size() != 0)
	{
		if (this->DIFS != 0)
		{
			this->DIFS -= TIME_INC;
			stat = dec_DIFS;
		}
		else if (!Transmitting)
		{
			if (this->backOff != 0)
			{
				this->backOff -= TIME_INC;
				stat = dec_BackOff;
			}
			else
			{
				sendMessage();
				stat = xmitting;
			}
		}
	}

	updateTime(t);

	return stat;
}

void Tx::sendMessage()
{
	this->sending = true;

	this->xfer_Time = DATA_FRAME_SIZE + SIFS + ACK;	// slots
}

void Tx::setBackOff()
{
	srand(time(0));

	this->backOff = rand() % (CWo - 1);
}

int Tx::transmit(int frames)
{
	return 0;
}

void Tx::collision(double col_num)
{
	srand(time(0));

	int CW = ((int)pow(2.0, col_num) * CWo - 1);

	if (CW > CWmax)
		CW = CWmax;

	this->backOff = rand() % CW;
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

