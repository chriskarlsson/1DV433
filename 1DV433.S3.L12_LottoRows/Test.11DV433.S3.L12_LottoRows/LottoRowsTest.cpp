#include <string>
#include "LottoRows.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Row doesn't contain duplicates", "[fillRow]")
{
    // Arrange
    const int MAXARRAYLENGTH = 35;
    int row[MAXARRAYLENGTH];

    // Act
    fillRow(row, MAXARRAYLENGTH);

    // Assert
    for (int i = 1; i < MAXARRAYLENGTH; i++)
    {
        for (int j = 0; i < i; j++)
        {
            REQUIRE(row[j] != row[i]);
        }
    }
}

TEST_CASE("Row is sorted", "[sortRow]")
{
    // Arrange
    int row[] = { 3, 1, 5, 1, 46, 0, -2, 3, 6 };

    // Act
    sortRow(row, sizeof(row)/sizeof(int));

    // Assert
    for (int i = 1; i < sizeof(row) / sizeof(int); i++)
    {
        REQUIRE(row[i-1] <= row [i]);
    }
}