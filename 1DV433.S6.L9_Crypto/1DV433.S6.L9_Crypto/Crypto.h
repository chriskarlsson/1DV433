#pragma once

#include <fstream>

void crypto(int argc, char * argv[]);

void parseArgument(int argc, char * argv[], int arg, char * target, int targetLength, const char * defaultString);

bool decrypt(char * encryptedFile, char * decryptedFile);

void openInputFile(char * inFileName, std::ifstream * inFile);

void openOutputFile(char * outFileName, std::ofstream * outFile);

void getString(char * target, int targetLength, const char * property);

bool binaryToChar(char * binaryChar, int const CHAR_BIT_SIZE, char & outChar);
