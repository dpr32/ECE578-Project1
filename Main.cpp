/*
Created By: Devan Roper & James
Date: 10/11/2017
Note:
    /|			  /\
   / |			 /  \
  /  |			/    \
     |		   /______\ 
     |		  /        \
     |		 /          \
_____|_____	/            \
*/
#include <iostream>
#include <vector>
#include <ctime>

#include "Tx.h"
#include "Main.h"
#include "Constants.h"

using namespace std;

bool Transmitting; 	// "false" Line is OPEN "true" Line is BUSY

int main()
{
	srand(0);

	int A_stat;
	int C_stat;

	Transmitting = false;

	Tx* A;
	Tx* C;

	A = new Tx(LAMDA_A);
	C = new Tx(LAMDA_C);

	int Current_Time = 0;
	int tot_collisions = 0;
	int consecutiveCollision = 0;

	while (Current_Time <= TIME_BLOCK)
	{
		A_stat = A->recieveTime(Current_Time);
		C_stat = C->recieveTime(Current_Time);

		if (A_stat == SENDING && C_stat == SENDING) // Collision
		{
			++consecutiveCollision;
			++tot_collisions;

			A->collision(consecutiveCollision);
			C->collision(consecutiveCollision);
		}
		else if (A_stat == SENDING || C_stat == SENDING)
		{
			Transmitting = true;
			consecutiveCollision = 0;
		}

		Current_Time += TIME_INC;
	}

	cout << "Total A collisions: " << A->getNumCollisions() << endl;
	cout << "Total A Xmissions: " << A->getNumACK() << endl;
	cout << "Total C collisions: " << C->getNumCollisions() << endl;
	cout << "Total C Xmissions: " << C->getNumACK() << endl;

	system("pause");

}


void generateTraffic(int lamda, vector<int> & v)
{
	double u = 0;
	double x = 0;
	double x_sec = 0;
	int tot = 0;

	while (x_sec < 10) // 10 sec
	{
		u = (rand() % 1000) / 1000.0;
		x = (-1.0 / lamda) * log(1.0 - u);
		x_sec += x;
		x = x * 1000000 / 10;  // slots [ ( x sec * 1000000 microsec/sec) / 10 microsec/slots ]
		x = round(x);
		tot += (int)x;

		v.push_back(tot);	//time is in slots!!
	}
}

