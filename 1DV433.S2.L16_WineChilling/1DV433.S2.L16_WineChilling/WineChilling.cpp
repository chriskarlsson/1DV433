//-----------------------------------------------------------------------
// File:    WineChilling.cpp
// Summary: Asks user for need information to calculate the time it takes
//          to chill a bottle of wine to a desired temperature and then
//          prints the result.
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

        const auto wineTemp = userInput("Enter the current temperature of the wine: ");
        const auto desiredWineTemp = userInput("Enter the desired temperature of the wine: ");
        const auto coolerTemp = userInput("Enter the temperature of the cooler: ");

        if (wineTemp < desiredWineTemp || desiredWineTemp < coolerTemp)
        {
            cout << "Invaldid input. Wine temperature must be higher than desired "
                 << "temperature which must be higher than the cooler temperature."
                 << endl;
            continue;
        }

        auto neededTime = calculateNeededTime(wineTemp, desiredWineTemp, coolerTemp);

        cout << endl << "It takes " << neededTime
             << " minutes for the wine to reach the desired temperature." << endl;
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
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a integer." << endl;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    cout << endl;

    // Check if answer is negative
    auto answer = input != "N" && input != "n";

    return answer;
}

//---------------------------------------------------------------------------
// int calculateNeededTime(int wineTemp, int desiredWineTemp, int coolerTemp)
//
// Summary: Calculates the time it takes to chill a bottle of wine to a
//          desired temperature
// Returns: Needed time in minutes
//---------------------------------------------------------------------------
int calculateNeededTime(int wineTemp, int desiredWineTemp, int coolerTemp)
{
    auto time = 0.0;
    auto currentTemp = (double)wineTemp;
    const auto tau = 50.0;

    // Step method to solve the differential equation
    while (currentTemp > desiredWineTemp)
    {
        currentTemp -= (currentTemp - coolerTemp) / tau * 0.1;
        time += 0.1;
    }

    return (int)round(time);
}