// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int rand1_5()
{
	return rand() % 5 + 1;
}

int rand0_3()
{
	int x = rand1_5();
	while (x == 5)
		x = rand1_5();

	return x - 1;
}

int rand0_1()
{
	int x = rand1_5();
	while (x == 3)
		x = rand1_5();

	return x>3;
}

int rand1_7()
{
	int x = rand0_1();
	int y = rand0_3();

	while (x == 0 && y == 0)
	{
		x = rand0_1();
		y = rand0_3();
	}
	return x*4+y;
}

// Construct rand1_7() from rand1_5()
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	const int N = 60000;

	
	int hist[7] = {0,0,0,0,0,0,0};
	for (int i = 0; i < N; i++)
	{
		hist[rand1_7() - 1]++;
	}

	for (int i = 0; i < 7; i++)
		cout << (float)hist[i]/N << endl;

	return 0;
}

