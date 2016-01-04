#include <iostream>
#include <sstream>
#include <set>

using namespace std;

// Implement an algorithm to determine if a string has all unique characters.
int main(int argc, char** argv)
{
	if (argc > 2) {
		cerr << "Num of arguments > 1!" << endl;
		return 1;
	}

	string str = string(argv[1]);
	set<char> str_set;
	for (int i = 0; i < str.length(); i++)
	{
		if (str_set.find(str[i]) == str_set.end())
			str_set.insert(str[i]);
		else
		{
			cout << "Repeated character: " << str[i] << endl;
			return 0;
		}
	}
	cout << "All unique!" << endl;
	return 0;
}
