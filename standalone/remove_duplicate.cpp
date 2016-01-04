#include <iostream>
#include <sstream>
#include <set>

using namespace std;

// Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. 
// NOTE: One or two additional variables are fine. An extra copy of the array is not.
int main(int argc, char** argv)
{
	if (argc > 2) {
		cerr << "Num of arguments > 1!" << endl;
		return 1;
	}

	string str = string(argv[1]);
	int j = 0;
	for (int i = 1; i < str.length(); i++)
	{
		while (str[i] == str[j])
			i++;
		str[++j] = str[i];
	}
	str.resize(j+1);
	cout << str << endl;
	return 0;
}
