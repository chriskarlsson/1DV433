//-----------------------------------------------------------------------
// Object: This program has some syntax errors. Use the compiler to find
// and correct them. Document your changes with comments or in log.
//-----------------------------------------------------------------------
// File:    CompileError.cpp
// Summary: This program calculates the weekly pay, given hours per week
// and wages per hour.
// Version: 1.2
// Owner:   Tommy L�fqvist
//-----------------------------------------------------------------------
// Log: 2005-03-09: Created the file, Mats!
//		2009-08-14: Revised by Tommy. Using manipulators to format output instead
//					of io-flags. Inserted "wait for return code" at the end.
//		2012-10-21: Revised by Anne. Converted to English version and VS 2012.
//		2014-11-11: Revised by Anne for VS 2013.
//		2017-10-31: Revised by Christoffer
//					Added missing # on includes
//					Changed main return type to int instead of void
//					Added missing type double on weeklyWages
//					Added missing ; on cout
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream> // Added missing #
#include <iomanip> // Added missing #
using namespace std;

int main() // Changed from void to int
{
	// Define and initialize variables
	int hoursPerWeek = 35;
	double hourlyWages = 83;

	// Calculate weekly wage
	double weeklyWages = hoursPerWeek * hourlyWages; // Type double

	// Show result
	cout << fixed			// Floating point format
		 << setprecision(2) // 2 decimals
		 << showpoint;		// Show trailing 0'os

	cout << "Given an hourly wage of " << hourlyWages << " kr" << endl
		<< " and the number of hours per week " << hoursPerWeek << endl
		<< " the weekly wages will be: " << weeklyWages << " kr" << endl; // Missing ;

	cout << "\nPress return!";
	cin.get();	// Wait for return

	return 0;
}
