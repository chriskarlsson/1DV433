#pragma once

using namespace std;

const int MAX_READ_INPUT_LENGTH = 100;
const int SOUNDEX_LENGTH = 4;

void soundex();

bool userYesOrNo(char * question);

void readName(char * name);

void encodeSoundex(const char * string, char * soundex);

char encodeCharacter(char c);

void printSoundex(char * soundex);