#include <iostream>
#include <vector>
#include <ctime>

#include "Tx.h"
#include "Main.h"
#include "Constants.h"

using namespace std;

double Current_Time;

bool Transmitting; 	// "false" Line is OPEN "true" Line is BUSY

int main()
{

	srand(time(0));
	int A_stat;
	int C_stat;

	int consecutiveCollision = 0;

	int tot_collisions = 0;

	Current_Time = 0;
	Transmitting = false;

	Tx A = Tx(LAMDA_A);
	Tx C = Tx(LAMDA_C);

	while (Current_Time <= TIME_BLOCK)
	{
		A_stat = A.recieveTime(Current_Time);
		C_stat = C.recieveTime(Current_Time);

		if (A_stat == SENDING && C_stat == SENDING) // Collision
		{
			++consecutiveCollision;
			++tot_collisions;

			A.collision(consecutiveCollision);
			C.collision(consecutiveCollision);
		}
		else if (A_stat == SENDING || C_stat == SENDING)
		{
			Transmitting = true;
			consecutiveCollision = 0;
		}

		Current_Time += TIME_INC;
	}

	cout << "Total collisions: " << tot_collisions << endl;
	cout << "Total A Xmissions: " << A.getNumACK() << endl;
	cout << "Total C Xmissions: " << C.getNumACK() << endl;

	system("pause");

}


void generateTraffic(int lamda, vector<double> & v)
{
	double u = 0;
	double x = 0;
	double x_sec = 0;
	double tot = 0;

	while (x_sec < 10) // 10 sec
	{
		u = (rand() % 1000) / 1000.0;
		x = (-1.0 / lamda) * log(1.0 - u);
		x_sec += x;
		x = x * 1000000 / 10;  // slots [ ( x sec * 1000000 microsec/sec) / 10 microsec/slots ]
		x = round(x);
		tot += x;

		v.push_back(tot);	//time is in slots!!
	}
}

