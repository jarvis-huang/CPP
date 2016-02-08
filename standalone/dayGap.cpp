#include <iostream>
#include <vector>
using namespace std;

enum Month {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

// days per month
const int dpm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int dpm_leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/***********************
This program counts the gap between two calendar dates.
For example, gap(2015/1/1,2015/1/2)=1.
Syntax:
	CPP.exe (no argument)

INPUT (one date per line in YYYY MM DD format)
-----
2015 4 6
2015 5 9

OUTPUT
------
Gap between 2015/4/6 and 2015/5/9 = 33
************************/


struct Day {
	int year;
	int month;
	int day;
};

class Year {
	int year;
public:
	Year(int y)
	{
		year = y;
	}
	bool isLeap() {
		if (year % 4 != 0)
			return false;
		else if (year % 100 != 0)
			return true;
		else if (year % 400 != 0)
			return false;
		else
			return true;
	}
	// get Days per Month
	int getDPM(int month)
	{
		if (isLeap())
			return dpm_leap[month - 1];
		else
			return dpm[month - 1];
	}
	// get Days per Year
	int getDPY() {
		if (isLeap())
			return 366;
		else
			return 365;
	}
};

// d1 must <= d2, otherwise return -1
int dayGap(Day d1, Day d2)
{	
	// Sanity check: d1 <= d2
	if (d1.year > d2.year)
		return -1;
	else if (d1.year == d2.year)
	{
		if (d1.month > d2.month)
			return -1;
		else if (d1.month == d2.month)
		{
			if (d1.day > d2.day)
				return -1;
		}
	}

	int count = 0;
	if (d1.year == d2.year)
	{
		Year year(d1.year);
		for (int m = d1.month; m <= d2.month; m++)
		{
			if (m>d1.month && m < d2.month)
				count += year.getDPM(m);
			else if (m == d1.month && m<d2.month)
				count += (year.getDPM(m) - d1.day);
			else if (m>d1.month && m == d2.month)
				count += d2.day;
			else // m==d1.month==d2.month
				count += (d2.day - d1.day);
		}
	}
	else
	{
		Day d1_tail = { d1.year, 12, 31 };
		Day d2_head = { d2.year, 1, 1 };
		count += dayGap(d1, d1_tail); // gap from d1 to 12/31 of same year
		count += dayGap(d2_head, d2); // gap from d2 to 1/1 of same year
		count++; // 12/31 to 1/1 is ONE day
		for (int y = d1.year + 1; y < d2.year; y++)
		{
			Year year(y);
			count += year.getDPY();
		}	
	}

	return count;
}

int main() {
	int y, m, d;
	cin >> y >> m >> d;
	Day d1 = { y, m, d };
	cin >> y >> m >> d;
	Day d2 = { y, m, d };
	cout << "Gap between " << d1.year << "/" << d1.month << "/" << d1.day << " and ";
	cout << d2.year << "/" << d2.month << "/" << d2.day << " = " << dayGap(d1, d2) << endl;
	
	return 0;
}


/*
// https://en.wikipedia.org/wiki/Leap_year#Algorithm
bool isLeap(int year) {
if (year % 4 != 0)
return false;
else if (year % 100 != 0)
return true;
else if (year % 400 != 0)
return false;
else
return true;
}

// get Days per Month
int getDPM(int year, int month)
{
if (isLeap(year))
return dpm_leap[month-1];
else
return dpm[month-1];
}

// get Days per Year
int getDPY(int year) {
if (isLeap(year))
return 366;
else
return 365;
}
*/