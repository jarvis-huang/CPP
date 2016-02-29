#include <iostream>
#include <sstream>
#include <cmath>

using namespace cv;
using namespace std;

/*
=== Fixed-point Notation ===
	ios::fmtflags old_settings = cout.flags();
	int old_precision = cout.precision();
    cout << fixed;
    cout.precision(2);
    // some work
	cout.flags(old_settings);
	cout.precision(old_precision);    

=== Scientific Notation ===
	ios::fmtflags old_settings = cout.flags();
	int old_precision = cout.precision();
    cout << scientific;
    cout.precision(2);
    // some work
	cout.flags(old_settings);
	cout.precision(old_precision);    
    
=== Formal way to set fixed/scientific
    cout.setf(std::ios_base::fixed, std::ios_base::floatfield); // fixed point
	cout.setf(std::ios_base::scientific, std::ios_base::floatfield); // scientific
*/  

int main(int argc, char** argv)
{
	// Save original setting
	int old_precision = cout.precision();
    
	// Apply new setting
	cout << fixed; // fixed point
    
    // This has different meaning under different settings:
    //             Mode                         Precision!=0                            Precision==0
    //           --------                        ----------                             -----------
    //            fixed                        # of digits after "."                      integer
    //          scientific                     # of digits after "." for mantissa       mantissa is integer     (exponent always 3-digit)
    //   default (non fixed/scientific)        total # of digits                        restore the 6-digit default
    // ================================================================================================================
	cout.precision(2); 
	
    // Do your work
	const long double pi = std::acos(-1.L);
	cout << "PI = " << pi * 100 << endl;
    
	// Restore original setting
	cout.setf(2, ios::floatfield);
	cout.precision(old_precision);

	return 0;
}