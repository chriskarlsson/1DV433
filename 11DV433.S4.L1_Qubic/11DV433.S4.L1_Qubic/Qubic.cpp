//-----------------------------------------------------------------------
// File:    Qubic.cpp
// Summary: Prints the calculated cube given the side length
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-04 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <cctype>
#include "Qubic.h"

using namespace std;

int main()
{
    // Headers
    cout << "Cubes" << endl;
    cout << "=====" << endl << endl;

    do
    {
        double side, volume;

        // Ask the user for the side length
        getSide(&side);

        // Calculate the volume
        volume = cubeVolume(side);

        // Print the volume
        printVolume(volume);
    } while (userWantOneMore());

    return 0;
}

//-----------------------------------------------------------------
// void getSide(double *side)
//
// Summary: Asks the user for the side length
// Returns: The side length as a double
//-----------------------------------------------------------------
void getSide(double *side)
{
    cout << "Enter the side length of the cube to be computed: ";
    cin >> *side;
}

//-----------------------------------------------------------------
// double cubeVolume(double side)
//
// Summary: Calculates the cube given the side length
// Returns: The cube volume as a double
//-----------------------------------------------------------------
double cubeVolume(double side)
{
    return side * side * side;
}

//-----------------------------------------------------------------
// void printVolume(double volume)
//
// Summary: Prints the cube volume
// Returns: -
//-----------------------------------------------------------------
void printVolume(double volume)
{
    cout << "Volume of cube is: " << volume << " volume units" << endl;
}

//-----------------------------------------------------------------
// bool userWantOneMore()
//
// Summary: Asks the user if another calculation is to be performed
// Returns: True if the answer is Y or y
//-----------------------------------------------------------------
bool userWantOneMore()
{
    char answer;

    cout << endl << "One more time (Y/N)? ";
    cin >> answer;

    return toupper(answer) == 'Y';
}