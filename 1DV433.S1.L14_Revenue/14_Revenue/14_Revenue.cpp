//-----------------------------------------------------------------------
// File:    Revenue.cpp
// Summary: Calculate the total amount after adding revenue for a given
//          number of years to an initial amount
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-11-03 File created by Christoffer
//-----------------------------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include "14_Revenue.h"

using namespace std;

#define REVENUE 3

int main()
{
    cout << "REVENUE ON REVENUE" << endl
         << "==================" << endl;

    do
    {
        cout << endl;

        auto value = userInput("Enter initial amount: ");
        auto years = userInput("Enter years         : ");

        auto total = calculateTotal(value, years);

        printTotal(years, total);
    } while (userWantOneMore());

    return 0;
}

//-----------------------------------------------------------------
// int userInput(string message)
//
// Summary: Prints the given request to the user and reads the user
//          input. The input is then sanitized.
// Returns: A positive integer.
//-----------------------------------------------------------------
int userInput(string message)
{
    int value;

    while (true) {
        // Print message and read response
        cout << message;
        cin >> value;

        // Check that input is valid and otherwise re-run
        if (cin.fail() || value < 0)
        {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    return value;
}

//-----------------------------------------------------------------
// double calculateTotal(int value, int years)
//
// Summary: Calculates the total after applying revenue to value
//          the given years.
// Returns: The total value
//-----------------------------------------------------------------

double calculateTotal(int value, int years)
{
    // Caclulate total
    return value * pow((1 + (double)REVENUE / 100), years);
}

//-----------------------------------------------------------------
// void printTotal(int years, double total)
//
// Summary: Prints the total value after given years with REVENUE.
// Returns: -
//-----------------------------------------------------------------
void printTotal(int years, double total)
{
    // Print explanation
    cout << endl
         << "Total amount after " << years
         << " with " << REVENUE << "% revenue is: ";

    // Print formatted total
    cout << fixed << showpoint << setprecision(2)
         << setfill('_') << setw(12) << right << total
         << " sek" << endl;
}

//-----------------------------------------------------------------
// bool userWantOneMore()
//
// Summary: Asks the user if the program should run one more time.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userWantOneMore()
{
    string answer;

    // Ask the user if program should re-run and read input
    cout << endl << "One more time? (Y/n): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, answer);

    // Check if answer is negative
    auto oneMore = answer != "N" && answer != "n";

    return oneMore;
}