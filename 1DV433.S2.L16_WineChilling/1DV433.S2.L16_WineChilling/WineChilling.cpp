//-----------------------------------------------------------------------
// File:    WineChilling.cpp
// Summary: Calculates the time it takes to chill a bottle of wine to a
//          desired temperature
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-11-11 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <string>
#include "WineChilling.h"

using namespace std;

//-----------------------------------------------------------------
// void wineChilling()
//
// Summary: Calculates the time it takes to chill a bottle of wine to a
//          desired temperature
// Returns: -
//-----------------------------------------------------------------
void wineChilling()
{
    char answer;
    do
    {

        auto wineTemp = userInput("Enter the current temperature of the wine: ");
        auto fridgeTemp = userInput("Enter the temperature of the refrigerator: ");
        auto desiredWineTemp = userInput("Enter the desired temperature of the wine: ");

    } while (userYesOrNo("One more time?"));
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
// bool userWantOneMore()
//
// Summary: Asks the user if the program should run one more time.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userYesOrNo(string question)
{
    string input;

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    // Check if answer is negative
    auto answer = input != "N" && input != "n";

    return answer;
}