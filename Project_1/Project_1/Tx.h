#include <iostream>
#include <vector>

using namespace std;



class Tx
{
private:

	int lamda;
	int DIFS = 2;
	int val_BO = 0;
	int numCollisions = 0;

	vector<double> Queue;
	vector<double> Traffic;

	double SIFS = 0.5;

public:

	Tx(int backOff, int lamda); //Constructor
	~Tx(); //Deconstructor

	string sendMessage();
	void backoff();
	int transmit(int frames);
	int generateTraffic();
	int recieveTime(int time);
	void collision(int col_num);

};

