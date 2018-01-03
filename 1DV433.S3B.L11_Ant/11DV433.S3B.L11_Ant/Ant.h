#pragma once

using namespace std;

struct result {
    int average;
    int max;
    int min;
};

struct square {
    int x;
    int y;
};

const int BOARDSIZE = 8;      // The size of the board (assuming square board) 
const int ITERATIONS = 1000;  // The number of times the ant walks the board

void ant();

bool userYesOrNo(string question);

result walkTheWalks(square startSquare, int iterations);

int simulateWalk(square square);

void move(square * square);

bool allSquaresVisited(bool board[BOARDSIZE][BOARDSIZE]);

void printResult(result result);

void print(string label, int value);
