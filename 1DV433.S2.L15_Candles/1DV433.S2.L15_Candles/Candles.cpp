//-----------------------------------------------------------------------
// File:    Windchill.cpp
// Summary: Calculates the perceived temperature given the measured temp
//          and wind speed
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-10-31 File created by Christoffer
// 
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include <math.h>
#include "Candles.h"

using namespace std;

int candles()
{
    char answer;
    do
    {
        auto measuredTemperature = userInput("Enter the temperature (degrees Celcius): ");
        auto windSpeed = userInput("Enter the wind speed (m/s): ");

        cout << "Perceived temperature: "
            << perceivedTemperature(measuredTemperature, windSpeed)
            << " degrees Celsius" << endl;

        cout << "One more time? (Y/N): ";
        cin >> answer;
    } while (answer == 'Y' || answer == 'y');

    return 0;
}

int userInput(string message)
{
    int value;
    while (true) {
        std::cout << message;
        cin >> value;

        if (cin.fail())
        {
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

int perceivedTemperature(int measuredTemp, int windSpeed)
{
    return (int)round(13.126667 + 0.6215 * measuredTemp - 13.924748 * pow(windSpeed, 0.16) + 0.4875195 * measuredTemp * pow(windSpeed, 0.16));
}
