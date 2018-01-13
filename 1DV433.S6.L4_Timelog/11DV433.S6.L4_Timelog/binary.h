#pragma once

void openInFile(int argc, char * argv[], char * inFilePath, std::ifstream * inFile);

bool writeToOutFile(std::ifstream * inFile, const char * outFileName);
