//-----------------------------------------------------------------------
// File:    Ant.cpp
// Summary: Simulates an ant walking over a chess board and prints how
//          many it has to walk the board until all squares are visited
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-03 File created by Christoffer
//-----------------------------------------------------------------------

// Preprocessor directives
#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include "Ant.h"

using namespace std;

//-----------------------------------------------------------------
// void ant()
//
// Summary: Simulates an ant walking over a chess board and prints how
//          many it has to walk the board until all squares are visited
// Returns: -
//-----------------------------------------------------------------
void ant()
{
    do
    {
        // Seed random number generator
        srand(time(NULL));

        // Ranodomize the starting point
        auto x = rand() % BOARDSIZE;
        auto y = rand() % BOARDSIZE;

        // Print a summary of the runs to be performed
        cout << "Starting point: (" << x << ", " << y << ")." << endl;
        cout << "Simulating " << ITERATIONS << " iterations." << endl;

        // Perform the walks
        result result = walkTheWalks({ x, y }, ITERATIONS);

        // Print the result
        printResult(result);
    } while (userYesOrNo("One more time?"));
}


//-----------------------------------------------------------------
// bool userWantOneMore()
//
// Summary: Asks the user if the program should run one more time.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userYesOrNo(string question)
{
    string input;

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    getline(cin, input);
    cout << endl;

    // Check if answer is negative
    auto answer = input != "N" && input != "n";

    return answer;
}

//-----------------------------------------------------------------
// void walkTheWalks(square startSquare, int iterations)
//
// Summary: Simulates the ant walking the board for the given
//          number of iterations
// Returns: Average, min and max needed steps per walk
//-----------------------------------------------------------------
result walkTheWalks(square startSquare, int iterations)
{
    auto total = 0;
    result result = { 0, 0, INT32_MAX };

    // Repeat the walking simulation for the given number of times
    for (int i = 0; i < iterations; i++) {
        auto steps = simulateWalk(startSquare);

        // Store the results
        total += steps;
        result.min = result.min < steps ? result.min : steps;
        result.max = result.max > steps ? result.max : steps;
    }

    // Calculate the average
    result.average = total / iterations;

    return result;
}

//-----------------------------------------------------------------
// int simulateWalk(square square)
//
// Summary: Simulates the ant walking the board for the given
//          number of iterations
// Returns: Average, min and max needed steps per walk
//-----------------------------------------------------------------
int simulateWalk(square square)
{
    // Define board matrix with all elements set to false
    bool board[BOARDSIZE][BOARDSIZE] = {false};
    auto steps = 0;

    // Initial square visited
    board[square.x][square.y] = true;

    // Repeat until returning
    while (true)
    {
        // Move to the next square
        move(&square);
        steps++;

        // Only check if all squares are visited if a square is visited for the
        // first time
        if (!board[square.x][square.y])
        {
            // Square visisted
            board[square.x][square.y] = true;

            // Check if all squares are visisted
            if (allSquaresVisited(board))
            {
                return steps;
            }
        }
    }
}

//-----------------------------------------------------------------
// void move(square *square, int *steps)
//
// Summary: Randomizes which square the ant should go to. Attempts
//          to walk outside the board are ignored.
// Returns: The square that the ant walks to.
//-----------------------------------------------------------------
void move(square *square)
{
    while (true)
    {
        // Generate a random value between 0-3 which will represent
        // the direction to move.
        auto movement = rand() % 4;

        // Make move and return if the move is within the board
        if (movement == 0 && square->x > 0)
        {
            (square->x)--;
            return;
        }
        else if (movement == 1 && square->x < BOARDSIZE - 1)
        {
            (square->x)++;
            return;
        }
        else if (movement == 2 && square->y > 0)
        {
            (square->y)--;
            return;
        }
        else if (movement == 3 && square->y < BOARDSIZE - 1)
        {
            (square->y)++;
            return;
        }
    }
}

//-----------------------------------------------------------------
// bool allSquaresVisited(bool  board[BOARDSIZE][BOARDSIZE])
//
// Summary: Checks if all squares on the board is visited.
// Returns: True if all squares are visited.
//-----------------------------------------------------------------
bool allSquaresVisited(bool  board[BOARDSIZE][BOARDSIZE])
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if (!board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

//-----------------------------------------------------------------
// void printResult(result result)
//
// Summary: Prints the result to the user.
// Returns: -
//-----------------------------------------------------------------
void printResult(result result)
{
    print("AVERAGE", result.average);
    print("MINIMUM VALUE", result.min);
    print("GEATEST VALUE", result.max);

    cout << endl;
}

//-----------------------------------------------------------------
// void print(string label, int value)
//
// Summary: Prints the label and the value formatted.
// Returns: -
//-----------------------------------------------------------------
void print(string label, int value)
{
    cout << left << setw(15) << label 
        << right << setw(5) << value 
        << " steps per walkaround" << endl;
}