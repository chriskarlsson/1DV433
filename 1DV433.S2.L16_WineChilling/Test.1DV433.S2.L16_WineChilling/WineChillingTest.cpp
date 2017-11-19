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
    auto desiredWineTemp = 16;
    auto coolerTemp = -18;

    // Act
    auto neededTime = calculateNeededTime(wineTemp, desiredWineTemp, coolerTemp);

    // Assert
    REQUIRE(neededTime == 12);
}

TEST_CASE("Test case 2", "[calculateNeededTime]")
{
    // Arrange
    auto wineTemp = 30;
    auto desiredWineTemp = 4;
    auto coolerTemp = -18;

    // Act
    auto neededTime = calculateNeededTime(wineTemp, desiredWineTemp, coolerTemp);

    // Assert
    REQUIRE(neededTime == 39);
}