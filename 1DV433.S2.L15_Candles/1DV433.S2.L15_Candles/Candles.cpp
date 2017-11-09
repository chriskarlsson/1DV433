//-----------------------------------------------------------------------
// File:    Candles.cpp
// Summary: Calculates the number of candle packages needed by a person
//          when celebrating birthdays
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-11-08 File created by Christoffer
//        2017-11-09 Added unit tests
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <string>
#include "Candles.h"

using namespace std;

//-----------------------------------------------------------------
// void candles()
//
// Summary: Calculates and prints the number of candle packages needed
//          by a person when celebrating birthdays
// Returns: -
//-----------------------------------------------------------------
void candles()
{
    char answer;
    do
    {
        int age = 100;
        int packageSize = 24;

        // Build string asking user wether to use default values
        stringstream ss;
        ss << "Use default values (" << age << " years "
           << packageSize << " candles/package)?";
        auto useDefault = ss.str();

        // Check if user wants to use default values and otherwise read them
        if (!userYesOrNo(useDefault))
        {
            age = userInput("Enter the age of the person: ");
            packageSize = userInput("Enter the size of the packages: ");
        }

        // Variables to be returned from calculation
        vector<int> consumption;
        int residualCandles;

        // Calculate consumption
        candleConsumption(age, packageSize, consumption, residualCandles);

        // Print
        printConsumption(consumption, residualCandles);
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

//-----------------------------------------------------------------
// void candleConsumption(int age,
//                        int packageSize,
//                        vector<int>& consumption,
//                        int& residualCandles)
//
// Summary: Calculates the candle consumption and residual candles
// Returns: vector<int> consumption and int residualCandles
//-----------------------------------------------------------------
void candleConsumption(int age,
                       int packageSize,
                       vector<int>& consumption,
                       int& residualCandles)
{
    residualCandles = 0;

    // Loop for each year
    for (int i = 0; i <= age; i++)
    {
        // Remove candles that is to be used
        residualCandles -= i;

        // Check if more packages are needed
        if (residualCandles < 0)
        {
            // Calculate needed number of packages
            auto boughtPackages = abs(residualCandles) / packageSize + 1;

            // Add needed number of packages to return vector
            consumption.push_back(boughtPackages);

            // Adjust residual candles
            residualCandles += boughtPackages * packageSize;
        }
        else
        {
            // Otherwise add zero to return vector
            consumption.push_back(0);
        }
    }
}

//-----------------------------------------------------------------
// void printConsumption(vector<int>& consumption,
//                       int residualCandles)
//
// Summary: Calculates the candle consumption and residual candles
// Returns: vector<int> consumption and int residualCandles
//-----------------------------------------------------------------
void printConsumption(vector<int>& consumption, int residualCandles)
{
    // Print headers
    cout << endl << setw(5) << left << "Year" << "Packages" << endl;

    // Print year and packages for each year when packages are bought
    for (int i = 0; i < consumption.size(); i++)
    {
        if (int packages = consumption[i])
        {
            cout << setw(5) << left << i << packages << endl;
        }
    }

    // Calculate the total number of packages
    auto totalNumberOfPackages = accumulate(consumption.begin(),
                                            consumption.end(),
                                            0);

    // Print summary
    cout << endl
         << "Total number of packages: " << totalNumberOfPackages << endl
         << "Residual candles: " << residualCandles << endl;
}