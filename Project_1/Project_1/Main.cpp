#include <iostream>
#include <vector>
#include <ctime>

#include "Constants.h"
#include "Tx.h"


using namespace std;

int Time_Blocks;
int Transmitting = 1; 	// "1" Line is OPEN "0" Line is BUSY

int main()
{
	int A_stat;
	int C_stat;

	int lamda = 100;

	int r1 = rand() % 4;
	int r2 = rand() % 4;

	srand(time(0));
	Time_Blocks = 0;

	Tx A = Tx(r1, lamda);
	Tx C = Tx(r2, lamda);

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