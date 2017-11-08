#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include <math.h>
#include "Candles.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Factorials are computed", "[perceivedTemperature]") {
    auto measuredTemp = 4;
    auto windSpeed = 10;
    auto expectedValue = -2;

    auto actualValue = perceivedTemperature(measuredTemp, windSpeed);

    REQUIRE(expectedValue == actualValue);
}