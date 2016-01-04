// CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

#define MAX_GUESS 10

// Word guessing game
int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> words;
	string line;
	ifstream myfile("words.txt");

	// Read words from a text file and store into a vector. Remove spaces and blank lines.
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.empty()) continue;

			int i = 0;
			while (line[i] == ' ')
				i++;
			int start_idx = i;
			int end_idx;
			for (; i < line.length(); i++)
			{
				if (line[i] == ' '){
					end_idx = i;
					words.push_back(line.substr(start_idx, end_idx - start_idx));
					while (line[i] == ' ')
						i++;
					start_idx = i;
				}
			}
			words.push_back(line.substr(start_idx, line.length() - start_idx));
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		return 1;
	}

	// Pick a random word
	srand(time(NULL));
	string pick = words.at(rand() % words.size());

	string guess, display = pick;
	for (int i = 0; i < display.length(); i++)
		display[i] = '_';
	
	int trial = 1;
	cout << "Your guess (" << trial << "/" << MAX_GUESS << "): ";
	while (getline(cin, guess))
	{
		if (guess == pick)
		{
			cout << "You Win!\n";
			break;
		}
		else
		{
			for (int i = 0; i < pick.length(); i++)
			{
				if (string(1,pick[i])==guess)
					display[i] = pick[i];
			}
			cout << display << endl;
			trial++;
			if (trial > MAX_GUESS)
			{
				cout << "You Lose!\n";
				cout << "Answer: " << pick << endl;
				break;
			}
			cout << "Your guess (" << trial << "/" << MAX_GUESS << "): ";
		}
	}

	return 0;
}

