#include <iostream>
#include <math.h>

#include "Constants.h"
#include "Main.h"
#include "Tx.h"

using namespace std;

extern int Transmitting;

Tx::Tx(int backOff, int lamda)    /*Constructor*/
{
	this->realTime = 0;
	this->nextTime = 0;
	
	this->lamda = lamda;
	this->val_BO = backOff;

	generateTraffic(lamda, this->Traffic);
}

Tx::~Tx()    /*Deconstructor*/
{
}

int Tx::recieveTime(double t)
{
	if (t == this->Traffic[0])
	{
		this->Queue.push(Traffic[0]);
		Traffic.pop_back();
	}

	updateTime(t);
}

string Tx::sendMessage()
{

}

void Tx::backoff()
{

}

int Tx::transmit(int frames)
{

}

void Tx::collision(int col_num)
{

}

void Tx::updateTime(double t)
{
	this->realTime = t;
}