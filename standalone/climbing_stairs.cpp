// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// https://leetcode.com/problems/climbing-stairs/

class Solution {
public:
	int climbStairs(int n) {
		if (n == 1 || n == 0)
			return 1;
		else
			return climbStairs(n - 1) + climbStairs(n - 2);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	string str;
	getline(cin, str);
	stringstream myStream(str);
	myStream >> n;

	Solution sol;
	cout << sol.climbStairs(n) << endl;
	return 0;
}

