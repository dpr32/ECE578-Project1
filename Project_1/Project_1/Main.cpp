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

		cout << "status of A: " << A_stat << endl;
		cout << "status of B: " << C_stat << endl;

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
	cout << "Total collisions: " << tot_collisions;

	system("pause");

}


void generateTraffic(int lamda, vector<double> & v)
{
	double sum = 0;
	double temp = 0;
	double tot = 0;
	v.push_back(0);
	for (int i = 1; i < 10 * lamda; ++i)
	{
		sum = 1.0 / (10 * lamda) + sum;
		temp = (-1.0 / lamda) * log(1.0 - sum) * TIME_BLOCK;
		temp = round(temp);
		tot += temp;

		v.push_back(tot);	//time is in blocks!!
	}
}

