// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// Determine little endian or big endian
int _tmain(int argc, _TCHAR* argv[])
{
	long int a = 1237;
	unsigned char* byte = (unsigned char*)&a; // by default char is signed
	cout << "BYTE0:" << std::hex << (int)byte[0] << endl; // if byte0 is 0xD5, machine is little-endian
	cout << "BYTE1:" << std::hex << (int)byte[1] << endl;
	
	return 0;
}

