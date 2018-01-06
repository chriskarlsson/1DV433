//-----------------------------------------------------------------------
// File:    Crypto.cpp
// Summary: Tries to decrypt a file containing a binary string and
//          writes the result to an output file using arguments
//          [inputFile] [outputFile]. Default values
//          are used if no arguments are given.
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-01-06 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <iomanip>
#include "Crypto.h"

using namespace std;

// Windows max path length including null char
const int MAX_PATH_LENGTH = 261;

//-----------------------------------------------------------------
// void crypto(int argc, char *argv[])
//
// Summary: Tries to decrypt a file containing a binary string and
//          writes the result to an output file using arguments
//          [inputFile] [outputFile]. Default values
//          are used if no arguments are given.
// Returns: -
//-----------------------------------------------------------------
void crypto(int argc, char *argv[])
{
    // Print help
    if ((argc == 2 && strcmp(argv[1], "-h") == 0))
    {
        cout << "usage: 1DV433.S6.L9_Crypto [inputFile] [outputFile]" << endl;
        return;
    }

    // Variables
    char inFileName[MAX_PATH_LENGTH] = "";
    char outFileName[MAX_PATH_LENGTH] = "";

    // Parse input
    parseArgument(argc, argv, 2, inFileName, MAX_PATH_LENGTH, "crypto.txt");
    parseArgument(argc, argv, 3, outFileName, MAX_PATH_LENGTH, "decrypted.txt");

    // Inform user wether the read/write was successful
    if (decrypt(inFileName, outFileName))
    {
        cout << endl << "Decrypted string written to: " << outFileName;
    }

    // Wait for user if running from Visual Studio
#ifdef _DEBUG
    cin.get();
#endif // DEBUG

    return;
}

//-----------------------------------------------------------------
// void parseArgument(int argc, char *argv[], int arg, char *target, int targetLength, const char *defaultString)
//
// Summary: Parse the given argument to target if available and
//          otherwise use the provided defaultString.
// Returns: -
//-----------------------------------------------------------------
void parseArgument(int argc, char *argv[], int arg, char *target, int targetLength, const char *defaultString)
{
    if (argc > arg && strlen(argv[arg]) < targetLength)
    {
        // Use argument if available and within the given limits
        strcpy_s(target, targetLength, argv[arg]);
    }
    else
    {
        // Otherwise use default string
        strcpy_s(target, targetLength, defaultString);
    }
}

//-----------------------------------------------------------------
// bool decrypt(char *encryptedFile, char *decryptedFile)
//
// Summary: Trying to decrypt encryptedFile and write the result to
//          stdOut and decryptedFile
// Returns: -
//-----------------------------------------------------------------
bool decrypt(char *encryptedFile, char *decryptedFile)
{
    // File streams
    ifstream inFile;
    ofstream outFile;

    // Open the files
    openInputFile(encryptedFile, &inFile);
    openOutputFile(decryptedFile, &outFile);

    // Read 8 bits at the time
    const int CHAR_BIT_SIZE = 8;
    char binaryChar[CHAR_BIT_SIZE];
    while (inFile.read(binaryChar, CHAR_BIT_SIZE))
    {
        char ch;

        // Convert bit string to ASCII char
        if (binaryToChar(binaryChar, CHAR_BIT_SIZE, ch))
        {
            // Write char to stdOut and file
            cout << ch;
            outFile << ch;
        }
        else
        {
            // Close files and delete empty output file on failing conversion
            inFile.close();
            outFile.close();
            remove(decryptedFile);
            return false;
        }
    }

    cout << endl;

    // Close files
    inFile.close();
    outFile.close();

    return true;
}

//-----------------------------------------------------------------
// void openInputFile(char *inFileName, ifstream *inFile)
//
// Summary: Tries to open inFileName file for reading in the stream
//          inFile. Asks user for input until succeeded.
// Returns: -
//-----------------------------------------------------------------
void openInputFile(char *inFileName, ifstream *inFile)
{
    // Try to open file until succeeded
    while (true)
    {
        // Try to open file
        inFile->open(inFileName, ios_base::in);

        // Check if file was possible to open
        if (inFile->is_open())
        {
            break;
        }

        // Otherwise ask user for input
        getString(inFileName, MAX_PATH_LENGTH, "input file");
    }
}

//-----------------------------------------------------------------
// void openOutputFile(char *outFileName, ofstream *outFile)
//
// Summary: Tries to open outFileName file for writing to the stream
//          outFile. Asks user for input until succeeded.
// Returns: -
//-----------------------------------------------------------------
void openOutputFile(char *outFileName, ofstream *outFile)
{
    // Try to open file until succeeded
    while (true)
    {
        // Try to open file
        outFile->open(outFileName, ios_base::out);

        // Check if file was possible to open
        if (outFile->is_open())
        {
            break;
        }

        // Otherwise ask user for input
        getString(outFileName, MAX_PATH_LENGTH, "output file");
    }
}

//-----------------------------------------------------------------
// void getString(char *target, int targetLength, const char *property)
//
// Summary: Asks the user for property and reads it to target
// Returns: -
//-----------------------------------------------------------------
void getString(char *target, int targetLength, const char *property)
{
    cout << endl << "Please enter " << property << ": ";
    cin.getline(target, targetLength);
    cout << endl;
}

//-----------------------------------------------------------------
// bool binaryToChar(char * binaryChar, int const CHAR_BIT_SIZE, char &character)
//
// Summary: Convert CHAR_BIT_SIZE long binaryChar to character
// Returns: -
//-----------------------------------------------------------------
bool binaryToChar(char * binaryChar, int const CHAR_BIT_SIZE, char &outChar)
{
    // Reset output char
    outChar = 0;

    // Loop trough bit string
    for (int i = 0; i < CHAR_BIT_SIZE; i++)
    {
        // Make sure each input char is binary (0 or 1)
        if (binaryChar[i] != '0' && binaryChar[i] != '1')
        {
            // Explain error and return false
            cout << endl << "Unexpected token: " << binaryChar[i] << ". Expected only 0 or 1." << endl;
            return false;
        }

        // Convert input char to int
        int bit = binaryChar[i] - '0';

        // Bitshift output char and add the latest bit
        outChar = (outChar << 1) + bit;
    }

    return true;
}