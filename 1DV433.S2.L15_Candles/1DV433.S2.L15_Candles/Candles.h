#pragma once

void candles();

int userInput(std::string message);

bool userYesOrNo(std::string question);

void candleConsumption(int age, int packageSize, std::vector<int>& consumption, int& residualCandles);

void printConsumption(std::vector<int>& consumption, int residualCandles);