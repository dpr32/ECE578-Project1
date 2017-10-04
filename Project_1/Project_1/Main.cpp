#include <iostream>
#include <vector>
#include <ctime>

#include "Tx.h"
#include "Main.h"
#include "Constants.h"

using namespace std;

double Time_Block;

bool Transmitting; 	// "false" Line is OPEN "true" Line is BUSY

int main()
{
	int A_stat;
	int C_stat;

	int numCollision = 0;

	int tot_collisions = 0;

	Time_Block = 0;
	Transmitting = false;

	Tx A = Tx(LAMDA_A);
	Tx C = Tx(LAMDA_C);

	while (Time_Block <= 500000)
	{
		A_stat = A.recieveTime(Time_Block);
		C_stat = C.recieveTime(Time_Block);

		if (A_stat == xmitting && C_stat == xmitting) // Collision
		{
			++numCollision;
			++tot_collisions;

			A.collision(numCollision);
			C.collision(numCollision);
		}
		else if (A_stat == xmitting || C_stat == xmitting)
		{
			Transmitting = true;
			numCollision = 0;
		}

		Time_Block += TIME_INC;
	}

	system("pause");

}