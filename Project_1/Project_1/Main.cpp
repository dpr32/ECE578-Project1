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

	int runtimes = 10;
	int Ave_collisions = 0;
	int ave_through_A = 0;
	int ave_through_C = 0;

	int tot_collisions = 0;

	Current_Time = 0;
	Transmitting = false;

	Tx* A;

	Tx* C;

	for (int i = 0; i < runtimes; ++i)
	{
		A = new Tx(LAMDA_A);
		C = new Tx(LAMDA_C);
		Current_Time = 0;

		while (Current_Time <= TIME_BLOCK)
		{
			A_stat = A->recieveTime(Current_Time);
			C_stat = C->recieveTime(Current_Time);

			if (A_stat == RTS && C_stat == RTS) // Collision
			{
				++consecutiveCollision;
				++tot_collisions;
			
				A->collision(consecutiveCollision);
				C->collision(consecutiveCollision);
			}
			else if (A_stat == CTS || C_stat == CTS)
			{
				Transmitting = true;
				consecutiveCollision = 0;
			}

			Current_Time += TIME_INC;
		}

		ave_through_A += A->getNumACK();
		ave_through_C += C->getNumACK();
		delete(A);
		delete(C);
		A = NULL;
		C - NULL;
	}

	cout << "Total collisions: " << (tot_collisions / runtimes) << endl;
	cout << "Total A Xmissions: " << (ave_through_A / runtimes) << endl;
	cout << "Total C Xmissions: " << (ave_through_C / runtimes) << endl;

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

