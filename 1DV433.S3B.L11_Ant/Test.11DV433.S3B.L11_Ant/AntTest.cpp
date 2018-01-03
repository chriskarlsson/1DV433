#include <string>
#include "ant.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Average, min and max are the same on first iteration", "[walkTheWalks]")
{
    // Arrange
    srand(1);
    auto startingPoint = 4;

    // Act
    auto result = walkTheWalks({ startingPoint, startingPoint }, 1);

    // Assert
    REQUIRE(result.average == result.min);
    REQUIRE(result.min == result.max);
}

TEST_CASE("Average is between min and max", "[walkTheWalks]")
{
    // Arrange
    srand(1);
    auto startingPoint = 4;
    auto smallestPossible = BOARDSIZE * BOARDSIZE;

    // Act
    auto result = walkTheWalks({ startingPoint, startingPoint }, 10);

    // Assert
    REQUIRE(smallestPossible < result.min);
    REQUIRE(result.min < result.average);
    REQUIRE(result.average < result.max);
}

TEST_CASE("Simulate walk resturn an integer", "[simulateWalk]")
{
    // Arrange
    srand(1);
    auto startingPoint = 4;
    auto smallestPossible = BOARDSIZE * BOARDSIZE;

    // Act
    auto result = simulateWalk({ startingPoint, startingPoint });

    // Assert
    REQUIRE(smallestPossible < result);
}

TEST_CASE("Not moving outside board on increase", "[move]")
{
    // Arrange
    srand(5); // Will genereate the serie 3 1 2  (incr y, incr x, decr x)
    auto startingPoint = BOARDSIZE - 1;
    square square = { startingPoint, startingPoint };
    // Act
    move(&square);

    // Assert
    REQUIRE((square.x < BOARDSIZE && square.y < BOARDSIZE));
    REQUIRE((square.x == BOARDSIZE - 2 || square.y == BOARDSIZE - 2));
}

TEST_CASE("Not moving outside board on decrease", "[move]")
{
    // Arrange
    srand(2); // Will genereate the serie 2 0 1 (decr y, decr x, incr x)
    auto startingPoint = 0;
    square square = { startingPoint, startingPoint };
    // Act
    move(&square);

    // Assert
    REQUIRE((square.x >= 0 && square.y >= 0));
    REQUIRE((square.x == 1 || square.y == 1));
}

TEST_CASE("All visited detected", "[allSquaresVisited]")
{
    // Arrange
    bool board[BOARDSIZE][BOARDSIZE] = { false };

    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            board[i][j] = true;
        }
    }

    // Act
    auto result = allSquaresVisited(board);

    // Assert
    REQUIRE(result);
}

TEST_CASE("Unvisited squares detected", "[allSquaresVisited]")
{
    // Arrange
    bool board[BOARDSIZE][BOARDSIZE] = { false };

    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            board[i][j] = true;
        }
    }

    board[BOARDSIZE - 1][BOARDSIZE - 1] = false;

    // Act
    auto result = allSquaresVisited(board);

    // Assert
    REQUIRE_FALSE(result);
}