#pragma once

#include <fstream>

void sms(int argc, char * argv[]);

void parseArgument(int argc, char * argv[], int arg, char * target, int targetLength, const char * defaultString);

bool senderFilter(char * logFileName, char * resultFileName, const char * sender);

void openInputFile(char * inFileName, std::ifstream * inFile);

void openOutputFile(char * outFileName, std::ofstream * outFile);

void getString(char * target, int targetLength, const char * property);