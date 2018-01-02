//-----------------------------------------------------------------------
// File:    binary.cpp
// Summary: Writes all mesaurements from logging point A to a text file.
//          Not unit tested due to high io.
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2018-01-02 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include "binary.h"

using namespace std;

// Format of measurements
struct DataRecord
{
    char logger;    // Logging Point
    double temp;    // Temperature  
    time_t locTime; // Local Time 
};

//-----------------------------------------------------------------
// int main(int argc, char *argv[])
//
// Summary: Writes all mesaurements from logging point A to a text file
// Returns: -
//-----------------------------------------------------------------
void main(int argc, char *argv[])
{
    // Print help
    if (argc == 2 && strcmp(argv[1], "-h"))
    {
        cout << "usage: 11DV433.S6.L4_Timelog [filePath]" << endl;
        return;
    }

    // Variables
    ifstream inFile;
    const char outFileName[] = "A.txt";
    char inFilePath[MAX_PATH];

    // Open binary file for reading
    openInFile(argc, argv, inFilePath, &inFile);

    // Write measurements to text file
    if (writeToOutFile(&inFile, outFileName))
    {
        cout << "Measurements written to " << outFileName;
    }
    else
    {
        // Inform user that writing failed
        cout << "Failed to open " << outFileName << " for writing. " << endl
            << "Make sure you have sufficient permissions.";
    }

    // Close files
    inFile.close();

    return;
}

//-----------------------------------------------------------------
// void openInFile(int argc, char *argv[], char *inFilePath, ifstream *inFile)
//
// Summary: Tries to open the requested binary file for reading in 
//          a stream. Asks user for input until succeeded.
// Returns: -
//-----------------------------------------------------------------
void openInFile(int argc, char *argv[], char *inFilePath, ifstream *inFile)
{
    if (argc != 2)
    {
        // Assume timelog.dat if no arguments are given
        strcpy_s(inFilePath, MAX_PATH, "timelog.dat");
    }
    else
    {
        // Otherwise use the first argument
        strcpy_s(inFilePath, MAX_PATH, argv[1]);
    }

    // Try to open file until succeeded
    while (true)
    {
        // Try to open file
        inFile->open(inFilePath, ios_base::binary | ios_base::in);

        // Check if file was possible to open
        if (inFile->is_open())
        {
            break;
        }

        // Otherwise ask user for input
        cout << "Failed to locate file. Please supply path: ";
        cin.getline(inFilePath, MAX_PATH);
    }
}

//-----------------------------------------------------------------
// bool writeToOutFile(ifstream *inFile, const char *outFileName)
//
// Summary: Writes the input stream to a text file
// Returns: True if writing was possible otherwise false
//-----------------------------------------------------------------
bool writeToOutFile(ifstream *inFile, const char *outFileName)
{
    // Buffer
    DataRecord measurementBuffer;

    // Try to open the file for writing
    ofstream outFile(outFileName, ios_base::out);

    // Return false if not possible
    if (!outFile.is_open())
    {
        return false;
    }

    // Write measurements as long as there are measurements in the file
    while (inFile->read((char *)&measurementBuffer, sizeof(measurementBuffer)))
    {
        // Check that the measurement is from point A
        if (measurementBuffer.logger == 'A')
        {
            // Buffers
            struct tm timeBuffer;
            char timeString[26];

            // Format time
            localtime_s(&timeBuffer, &measurementBuffer.locTime);
            asctime_s(timeString, &timeBuffer);

            // Write to file
            outFile << setprecision(1) << fixed << measurementBuffer.temp << ", " << timeString;
        }
    }

    // Close file
    outFile.close();

    return true;
}