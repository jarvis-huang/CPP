// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// Bucket sort (aka counting sort)
int _tmain(int argc, _TCHAR* argv[])
{
	int input[] = { 5, 9, 0, 4, 2, 4, 8, 2 }; // value between 0~9
	int n = 8;  // # of input
	int k = 10; // # of possible values = bucket count
	int* output = new int[n]; // sorted output

	int* count = new int[k];
	for (int i = 0; i < k; i++)
		count[i] = 0;

	// Initialize histogram (size=k)
	for (int i = 0; i < n; i++)
		count[input[i]]++;

	// Calculate the starting index for each bucket
	int total = 0; // total # of items before current bucket = current bucket starting address in the output array
	for (int i = 0; i < k; i++)
	{
		int old_count = count[i];
		count[i] = total;
		total += old_count;
	}

	// Throw each item into corresponding bucket, move each bucket's starting address forward by 1
	for (int i = 0; i < n; i++)
	{
		output[count[input[i]]] = input[i];
		count[input[i]]++;
	}

	// Print output
	for (int i = 0; i < n; i++)
		cout << output[i] << " ";
	
	cout << endl;
	
	return 0;
}

