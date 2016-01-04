#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <assert.h>
using namespace std;

#define N 5
#define M 5
int mat[N][M] = {
	{ 3, 0, 1, 4, 2 },
	{ 5, 6, 3, 2, 1 },
	{ 1, 2, 0, 1, 5 },
	{ 4, 1, 0, 1, 7 },
	{ 1, 0, 3, 0, 5 }
};

template <typename T>
T string2num(const string& str)
{
	T i;
	stringstream ss(str); 
	assert(ss >> i);
	return i;
}

// https://leetcode.com/problems/range-sum-query-2d-immutable/
int main(int argc, char* argv[])
{
	if (argc != 5) {
		cerr << "Num of arguments must be 4!\n";
		return 1;
	}

	int x1 = string2num<int>(argv[1]);
	int y1 = string2num<int>(argv[2]);
	int x2 = string2num<int>(argv[3]);
	int y2 = string2num<int>(argv[4]);

	cout << x1 << "," << y1 << "," << x2 << "," << y2 << endl;

	int sum = 0;
	for (int row = x1 - 1; row <= x2 - 1; row++)
	{
		for (int col = y1 - 1; col <= y2 - 1; col++)
		{
			sum += mat[row][col];
		}
	}
	
	cout << "Sum = " << sum << endl;

}