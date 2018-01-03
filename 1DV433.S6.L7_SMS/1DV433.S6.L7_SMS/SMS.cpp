//-----------------------------------------------------------------------
// File:    Main.cpp
// Summary: The main function of 1DV433.S6.L7_SMS
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-01-03 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <fstream>
#include <iostream>
#include <iomanip>
#include "SMS.h"

using namespace std;

// String lengths including null char
const int MAX_PATH_LENGTH = 261;
const int PHONE_NUMBER_LENGTH = 13;
const int MAX_TIME_LENGTH = 17;
const int MAX_SMS_LENGTH = 256;

// Format of SMS entry
struct SMS
{
    char sender[PHONE_NUMBER_LENGTH];
    char receiver[PHONE_NUMBER_LENGTH];
    char time[MAX_TIME_LENGTH];
    char text[MAX_SMS_LENGTH];
};

//-----------------------------------------------------------------
// void sms(int argc, char *argv[])
//
// Summary: Filters SMS log files on given arguments according to
//          [phoneNumber] [inputFile] [outputFile]. Default values
//          are used if no arguments are given.
// Returns: -
//-----------------------------------------------------------------
void sms(int argc, char *argv[])
{
    // Print help
    if ((argc == 2 && strcmp(argv[1], "-h") == 0))
    {
        cout << "usage: 1DV433.S6.L7_SMS [phoneNumber] [inputFile] [outputFile]" << endl;
        return;
    }

    // Variables
    char phoneNumber[PHONE_NUMBER_LENGTH] = "";
    char inFileName[MAX_PATH_LENGTH] = "";
    char outFileName[MAX_PATH_LENGTH] = "";

    // Parse input
    parseArgument(argc, argv, 1, phoneNumber, PHONE_NUMBER_LENGTH, "0702-235689");
    parseArgument(argc, argv, 2, inFileName, MAX_PATH_LENGTH, "smslog_eng.txt");
    parseArgument(argc, argv, 3, outFileName, MAX_PATH_LENGTH, "smslog_eng_filtered.txt");

    // Inform user wether the read/write was successful
    if (senderFilter(inFileName, outFileName, phoneNumber))
    {
        cout << "Measurements written to " << outFileName;
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
// bool senderFilter(char *logFileName, char *resultFileName, const char *sender)
//
// Summary: Filters the content of logFileName for sender and writes
//          the result to resultFileName.
// Returns: True if everything went as expected.
//-----------------------------------------------------------------
bool senderFilter(char *logFileName, char *resultFileName, const char *sender)
{
    // File streams
    ifstream inFile;
    ofstream outFile;

    // Open the files
    openInputFile(logFileName, &inFile);
    openOutputFile(resultFileName, &outFile);

    // Read one SMS at the time
    SMS sms;
    int counter = 0;
    while (inFile.getline(sms.sender, PHONE_NUMBER_LENGTH - 1) &&
        inFile.getline(sms.receiver, PHONE_NUMBER_LENGTH - 1) &&
        inFile.getline(sms.time, MAX_PATH_LENGTH - 1) &&
        inFile.getline(sms.text, MAX_SMS_LENGTH - 1))
    {
        // Copy to output file if sender is correct
        if (strcmp(sms.sender, sender) == 0)
        {
            outFile << sms.sender << endl
                << sms.receiver << endl
                << sms.time << endl
                << sms.text << endl;

            counter++;
        }
    }

    // Close input file
    inFile.close();
    outFile.close();

    if (counter == 0)
    {
        // No entries found
        cout << sender << " not found. Is the number correct?" << endl;
        remove(resultFileName); // Remove empty file created on open
        return false;
    }
    else if (!outFile)
    {
        // Writing failed
        cout << "Failed to write file. Do you have the correct permissions?" << endl;
        return false;
    }
    else
    {
        // Success
        return true;
    }
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