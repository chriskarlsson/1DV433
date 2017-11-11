#include <vector>
#include <numeric>
#include "WineChilling.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Test case 1", "[calculateNeededTime]")
{
    // Arrange
    auto wineTemp = 25;
    auto fridgeTemp = 16;
    auto desiredWineTemp = 18;

    // Act
    auto neededTime = calculateNeededTime(wineTemp, fridgeTemp, desiredWineTemp);

    // Assert
    REQUIRE(neededTime == 12);
}

TEST_CASE("Test case 2", "[calculateNeededTime]")
{
    // Arrange
    auto wineTemp = 30;
    auto fridgeTemp = 4;
    auto desiredWineTemp = -18;

    // Act
    auto neededTime = calculateNeededTime(wineTemp, fridgeTemp, desiredWineTemp);

    // Assert
    REQUIRE(neededTime == 39);
}