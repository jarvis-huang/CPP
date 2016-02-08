// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


/*
https://www.codechef.com/problems/LCH15JAB
You are given a string. Your task is to determine whether number of occurrences
of some character in the string is equal to the sum of the numbers of occurrences
of other characters in the string.
Input:
The first line of the input contains an integer T denoting the number of test cases. 
Each of the next T lines contains one string S consisting of lowercase latin letters.
Output:
For each test case, output a single line containing "YES" if the string satisfies the condition
given above or "NO" otherwise.
Example:

Input:
4
acab
zzqzqq
abc
kklkwwww
Output:
YES
YES
NO
YES
*/

bool checkString(string str)
{
	int len = str.length();
	
	// Always false if odd length
	if (len % 2 == 1)
		return false;

	map<char, int> histo;
	for (int i = 0; i < len; i++)
	{
		if (histo.count(str[i])>0)
			histo.at(str[i])++;
		else
			histo.emplace(str[i], 1);
	}

	// Check if any char's count == str.len/2
	for (map<char, int>::iterator ii = histo.begin(); ii != histo.end(); ++ii)
	{
		if (ii->second == len / 2)
			return true;
	}
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> words;
	string str;
	int n_cases;

	getline(cin, str);
	stringstream myStream(str);
	myStream >> n_cases;

	vector<bool> results;
	for (int i = 0; i < n_cases; i++)
	{
		getline(cin, str);
		if (str.empty())
			return 1;
		results.push_back(checkString(str));
	}


	// Display results
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i])
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}

