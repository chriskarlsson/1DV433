#include <vector>
#include <numeric>
#include "Candles.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Next package at 7 years", "[candleConsumption]")
{
    int age = 7;
    int packageSize = 24;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, consumption, residualCandles);

    REQUIRE(consumption[age] == 1);
}

TEST_CASE("Four packages at 97 years", "[candleConsumption]")
{
    int age = 97;
    int packageSize = 24;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, consumption, residualCandles);

    REQUIRE(consumption[age] == 4);
}

TEST_CASE("Total consumption", "[candleConsumption]")
{
    int age = 100;
    int packageSize = 24;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, consumption, residualCandles);

    auto totalPackages = accumulate(consumption.begin(), consumption.end(), 0);

    REQUIRE(totalPackages == 211);
    REQUIRE(residualCandles == 14);
}