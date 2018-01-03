//-----------------------------------------------------------------------
// File:    Again.cpp
// Summary: Reads integers and then prints them
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-17 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "Again.h"

using namespace std;

//-----------------------------------------------------------------
// void again()
//
// Summary: Reads integers and then prints them
// Returns: -
//-----------------------------------------------------------------
void again()
{
    do
    {
        int *numbers = nullptr;
        int numbersLength = 0;

        getNumbers(numbers, numbersLength);

        printNumbers(numbers, numbersLength);

        cleanup(numbers);
    } while (oneMoreTime());
}


//-----------------------------------------------------------------
// bool oneMoreTime()
//
// Summary: Asks the user if the progrom should re-run
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool oneMoreTime()
{
    string input;

    // Ask the user if program should re-run and read input
    cout << endl << "One more time? (Y/n): ";
    getline(cin, input);
    cout << endl;

    // Check if answer is negative
    auto oneMoreTime = toupper(input[0]) != 'N';

    return oneMoreTime;
}

//-----------------------------------------------------------------
// void getNumbers(int *&numbers, int &size)
//
// Summary: Asks the user for integers and adds them to the array
// Returns: -
//-----------------------------------------------------------------
void getNumbers(int *&numbers, int &size)
{
    string input;

    cout << "Enter integer numbers to store (cancel with 'stop')" << endl;

    do
    {
        // Read one word
        cin >> input;

        // Add it to array if it is an integer
        addIfNumber(numbers, size, input);
    } while (!isStop(input));
}

//-----------------------------------------------------------------
// void addIfNumber(int *&numbers, int &size, string input)
//
// Summary: Adds input to int array if it is a number
// Returns: -
//-----------------------------------------------------------------
void addIfNumber(int *&numbers, int &size, string input)
{
    int value;
    stringstream ss(input);

    // Try to cast string to integer
    if (ss >> value)
    {
        // Make room for the new value
        expandArray(numbers, size);

        // Add to array
        numbers[size - 1] = value;
    }
}

//-----------------------------------------------------------------
// void expandArray(int *&array, int &size)
//
// Summary: Increase array size by one
// Returns: -
//-----------------------------------------------------------------
void expandArray(int *&array, int &size)
{
    // Create temp variables
    int *newArray;
    int newSize = size + 1;

    try
    {
        // Allocate memory
        newArray = new int[newSize];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Copy all values from the old array to the new array
    for (int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }

    // Cleanup
    delete[] array;

    // Point old to the temp values
    array = newArray;
    size = newSize;
}


bool isStop(string &input)
{
    // Convert string to lower case to make comparision case insensitive
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    return input == "stop";
}

//-----------------------------------------------------------------
// void printNumbers(int *numbers, int size)
//
// Summary: Prints the given numbers
// Returns: -
//-----------------------------------------------------------------
void printNumbers(int *numbers, int size)
{
    cout << "Numbers:";

    // Loop over interger array
    for (int i = 0; i < size; i++)
    {
        cout << " " << *numbers++;
    }

    cout << endl;
}

//-----------------------------------------------------------------
// void cleanup(int *numbers)
//
// Summary: Free int array memory and clean cin
// Returns: -
//-----------------------------------------------------------------
void cleanup(int *numbers)
{
    delete[] numbers;
    numbers = nullptr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}