//-----------------------------------------------------------------------
// File:    LottoRows.cpp
// Summary: Prints a random, ordered lotto row of unique, positive
//          integers between 1 and 35
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-11-29 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include "LottoRows.h"

using namespace std;

const int ROWLENGTH = 7;  // This number has to be lower or equal to 
const int MAXNUMBER = 35; // this number or there will be an infinite
                          // loop

//-----------------------------------------------------------------
// void lottoRows()
//
// Summary: Creates a random ordered lotto row and prints it
// Returns: -
//-----------------------------------------------------------------
void lottoRows()
{
    do
    {
        int row[ROWLENGTH];

        fillRow(row, ROWLENGTH);
        sortRow(row, ROWLENGTH);
        printRow(row, ROWLENGTH);
    } while (userYesOrNo("One more time?"));
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
    getline(cin, input);
    cout << endl;

    // Check if answer is negative
    auto answer = input != "N" && input != "n";

    return answer;
}


//-----------------------------------------------------------------
// void fillRow(int row[], int arrayLength)
//
// Summary: Fills the given array with random unique integers
// Returns: -
//-----------------------------------------------------------------
void fillRow(int row[], int arrayLength)
{
    // Seed random number generator
    srand(time(NULL));

    // Loop over given array
    for (int i = 0; i < arrayLength; i++) {
        bool uniqueValue;
        int number;

        do
        {
            // Generate random number
            number = rand() % MAXNUMBER + 1;

            // Check that the number isn't already in the list
            uniqueValue = true;
            for (int j = 0; j < i; j++)
            {
                if (row[j] == number)
                {
                    uniqueValue = false;
                }
            }
        } while (!uniqueValue);

        // Add number to array
        row[i] = number;
    }
}

//-----------------------------------------------------------------
// void sortRow(int row[], int arrayLength)
//
// Summary: Sorts the given array using the insert sort algorithm
// Returns: -
//-----------------------------------------------------------------
void sortRow(int row[], int arrayLength)
{
    // Stop recursion whe reaching start of array
    if (arrayLength > 1)
    {
        // Recurse over the array from end to beginning
        sortRow(row, arrayLength - 1);
        // Last element of the array segment
        auto x = row[arrayLength-1];
        // Index of the element before
        auto j = arrayLength - 2;
        // Move each element one step to the right while x is larger
        while (j >= 0 && row[j] > x)
        {
            row[j + 1] = row[j];
            j -= 1;
        }

        // Insert x
        row[j + 1] = x;
    }
}

//-----------------------------------------------------------------
// void printRow(int row[], int arrayLength)
//
// Summary: Prints the given row
// Returns: -
//-----------------------------------------------------------------
void printRow(int row[], int arrayLength)
{
    for (int i = 0; i < arrayLength; i++) {
        cout << setw(3) << row[i];
    }

    cout << endl;
}