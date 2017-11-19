#include <vector>
#include <numeric>
#include "Candles.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("First package at 7 years", "[candleConsumption]")
{
    int age = 7;
    int packageSize = 24;
    int initialPackages = 1;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, initialPackages, consumption, residualCandles);
    auto sum = accumulate(consumption.begin(), consumption.end(), 0);

    REQUIRE(sum == 1);
}

TEST_CASE("Five packages at 97 years", "[candleConsumption]")
{
    int age = 97;
    int packageSize = 24;
    int initialPackages = 1;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, initialPackages, consumption, residualCandles);

    REQUIRE(consumption[age] == 5);
}

TEST_CASE("Total consumption", "[candleConsumption]")
{
    int age = 100;
    int packageSize = 24;
    int initialPackages = 1;
    vector<int> consumption;
    int residualCandles;

    candleConsumption(age, packageSize, initialPackages, consumption, residualCandles);

    auto totalPackages = accumulate(consumption.begin(), consumption.end(), initialPackages);

    REQUIRE(totalPackages == 211);
    REQUIRE(residualCandles == 14);
}