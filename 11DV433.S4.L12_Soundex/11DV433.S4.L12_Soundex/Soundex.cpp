//-----------------------------------------------------------------------
// File:    Soundex.cpp
// Summary: Asks a user for a name and prints the soundex representation
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-10 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Soundex.h"

using namespace std;

//-----------------------------------------------------------------
// void soundex()
//
// Summary: Asks a user for a name and prints the soundex
//          representation
// Returns: -
//-----------------------------------------------------------------
void soundex()
{
    do
    {
        char soundexName[SOUNDEX_LENGTH + 1];
        char name[MAX_READ_INPUT_LENGTH];

        readName(name);
        encodeSoundex(name, soundexName);
        printSoundex(soundexName);
    } while (userYesOrNo("One more time?"));
}


//-----------------------------------------------------------------
// bool userYesOrNo(char *question)
//
// Summary: Asks the user the supplied question.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userYesOrNo(char *question)
{
    char input[MAX_READ_INPUT_LENGTH];

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    cin.getline(input, MAX_READ_INPUT_LENGTH);
    cout << endl;

    // Check if answer is negative
    auto answer = toupper(input[0]) != 'N';

    return answer;
}


//-----------------------------------------------------------------
// void readName(char * name)
//
// Summary: Asks the user for a name and assigns it to the argument
//          cstring
// Returns: -
//-----------------------------------------------------------------
void readName(char * name)
{
    do
    {
        cout << "Enter a name: ";
        cin.getline(name, MAX_READ_INPUT_LENGTH);
    } while (strlen(name) <= 0);
}

//-----------------------------------------------------------------
// void encodeSoundex(const char *string, char *soundex)
//
// Summary: Converts the given string to its soundex represetation
//          and assigns it to the supplied char array
// Returns: -
//-----------------------------------------------------------------
void encodeSoundex(const char *string, char *soundex)
{
    int soundexIndex = 0;

    // Only convert if first char is a letter
    if (isalpha(string[0]))
    {
        // First char is an uppercase letter
        soundex[soundexIndex++] = toupper(string[0]);

        // Loop over the given string until it ends or a full soundex is acheived
        for (int stringIndex = 1;
             string[stringIndex] != '\0' && soundexIndex < SOUNDEX_LENGTH;
             stringIndex++)
        {
            auto encodedChar = encodeCharacter(string[stringIndex]);

            // Only add chars that has a mapping and isn't the same as the previous
            if (encodedChar != '\0' && encodedChar != soundex[soundexIndex - 1])
            {
                soundex[soundexIndex++] = encodedChar;
            }
        }
    }

    // Pad the soundex with '0'
    while (soundexIndex < SOUNDEX_LENGTH)
    {
        soundex[soundexIndex++] = '0';
    }

    // Add null to indicate end of string
    soundex[soundexIndex] = '\0';
}

//-----------------------------------------------------------------
// char encodeCharacter(char c)
//
// Summary: Converts given char to its numerical representation
// Returns: Numerical char. Null char ('\n') if no mapping exists.
//-----------------------------------------------------------------
char encodeCharacter(char c)
{
    switch (toupper(c))
    {
    case 'B':
    case 'P':
    case 'F':
    case 'V':
        return '1';
    case 'C':
    case 'G':
    case 'J':
    case 'K':
    case 'Q':
    case 'S':
    case 'X':
    case 'Z':
        return '2';
    case 'D':
    case 'T':
        return '3';
    case 'L':
        return '4';
    case 'M':
    case 'N':
        return '5';
    case 'R':
        return '6';
    default:
        return '\0';
    }
}

//-----------------------------------------------------------------
// void printName(string name)
//
// Summary: Prints the given soundex
// Returns: -
//-----------------------------------------------------------------
void printSoundex(char *soundex)
{
    cout << "Soundex: " << soundex << endl;
}