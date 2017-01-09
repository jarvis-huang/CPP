#include <iostream>
using namespace std;

void main (void)
{
	int a, b, c;
	char ch = 'a';
	a = 76;
	b = 77;
	c = a ^ b;
	if (!c)
		cout << "Equal: " << c;
	else
		cout << "Different" << c;
	
	cout << (int)ch;
}
	