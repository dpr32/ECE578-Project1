#include <iostream>
#include <vector>
#include "Tx.h"
#include "Constants.h"

using namespace std;

int Transmitting;
int Time_Blocks;

int main()
{
	Transmitting = 1;	// "1" Line is OPEN "0" Line is BUSY

	Tx A = Tx(rand() % 4);
	Tx C = Tx(rand() % 4);

	Time_Blocks = 0;
	int A_stat;
	int C_stat;

	while (Time_Blocks <= 500000)
	{
		A_stat = A.recieveTime(Time_Blocks);
		C_stat = C.recieveTime(Time_Blocks);

		if (A_stat == 0 && C_stat == 0) // Collision
		{

		}

		Time_Blocks += 0.1;
	}

}