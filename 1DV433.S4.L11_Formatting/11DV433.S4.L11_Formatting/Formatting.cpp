//-----------------------------------------------------------------------
// File:    Formatting.cpp
// Summary: Formats a given name to remove superfluous white spaces and set
//          the first letter of each part uppercase and the rest lower case
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-05 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include "Formatting.h"

using namespace std;

//-----------------------------------------------------------------
// void formatting()
//
// Summary: Asks a user for a name and prints the formatted version
// Returns: -
//-----------------------------------------------------------------
void formatting()
{
    do
    {
        const auto name = readName();
        if (isValidName(name))
        {
            const auto formattedName = formatName(name);
            printName(formattedName);
        }
        else
        {
            cout << "Name contain invalid characters. "
                << "Only english letters and whitespace is accepted." << endl;
        }
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
// string readName()
//
// Summary: Asks the user for a name
// Returns: Given name as a string
//-----------------------------------------------------------------
string readName()
{
    string name;

    do
    {
        cout << "Enter a name: ";
        getline(cin, name);
    } while (name.length() <= 0);

    return name;
}

//-----------------------------------------------------------------
// bool isValidName(string name)
//
// Summary: Verifies that the given name only contain valid characters
// Returns: True if all chars are whitespace or alphabetical
//-----------------------------------------------------------------
bool isValidName(string name)
{
    for (int i = 0; i < name.length(); i++)
    {
        // Verify that each char is white space or alphabetical
        if (!iswspace(name[i]) && !isalpha((unsigned char)name[i]))
        {
            return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------
// string formatName(string name)
//
// Summary: Formats the given name
// Returns: Name as formatted string
//-----------------------------------------------------------------
string formatName(string name)
{
    string formatName;
    auto previousIsBlank = true;

    // Loop over the given string
    for (int i = 0; i < name.length(); i++)
    {
        if (iswspace(name[i]))
        {
            if (!previousIsBlank)
            {
                // Only add space if the previous isn't a whitespace
                formatName += ' ';
                previousIsBlank = true;
            }
        }
        else if(previousIsBlank)
        {
            // Add first letter of each word as upper case
            formatName += toupper(name[i]);
            previousIsBlank = false;
        }
        else
        {
            // Add the rest of the letters as lower case
            formatName += tolower(name[i]);
        }
    }

    // Remove trailing white space
    if (previousIsBlank)
    {
        formatName.pop_back();
    }

    return formatName;
}

//-----------------------------------------------------------------
// void printName(string name)
//
// Summary: Prints the given string
// Returns: -
//-----------------------------------------------------------------
void printName(string name)
{
    cout << "Formatted name: ->" << name << "<-" << endl;
}