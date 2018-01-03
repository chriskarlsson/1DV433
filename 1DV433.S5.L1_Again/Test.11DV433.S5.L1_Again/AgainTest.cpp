#include <string>
#include "Again.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Adding number", "[addIfNumber]")
{
    // Arrange
    int *numbers = nullptr;
    int numbersLength = 0;
    string value = "2";

    // Act
    addIfNumber(numbers, numbersLength, value);

    // Assert
    REQUIRE(numbers[0] == 2);
    REQUIRE(numbersLength == 1);

    // Cleanup
    delete[] numbers;
}

TEST_CASE("Adding negative number", "[addIfNumber]")
{
    // Arrange
    int *numbers = nullptr;
    int numbersLength = 0;
    string value = "-1";

    // Act
    addIfNumber(numbers, numbersLength, value);

    // Assert
    REQUIRE(numbers[0] == -1);
    REQUIRE(numbersLength == 1);

    // Cleanup
    delete[] numbers;
}

TEST_CASE("Adding more than one", "[addIfNumber]")
{
    // Arrange
    int *numbers = nullptr;
    int numbersLength = 0;
    string value = "2";

    // Act
    addIfNumber(numbers, numbersLength, value);
    addIfNumber(numbers, numbersLength, value);

    // Assert
    REQUIRE(numbers[1] == 2);
    REQUIRE(numbersLength == 2);

    // Cleanup
    delete[] numbers;
}

TEST_CASE("Not adding NAN", "[addIfNumber]")
{
    // Arrange
    int *numbers = nullptr;
    int numbersLength = 0;
    string value = "Not a number";

    // Act
    addIfNumber(numbers, numbersLength, value);

    // Assert
    REQUIRE(numbers == nullptr);
    REQUIRE(numbersLength == 0);
}

TEST_CASE("Detecting stop", "[isStop]")
{
    // Arrange
    string input = "stop";

    // Act
    bool stop = isStop(input);

    // Assert
    REQUIRE(stop);
}

TEST_CASE("Detecting stop case insensitive", "[isStop]")
{
    // Arrange
    string input = "StOp";

    // Act
    bool stop = isStop(input);

    // Assert
    REQUIRE(stop);
}

TEST_CASE("Not detecting non stop", "[isStop]")
{
    // Arrange
    string input = "start";

    // Act
    bool stop = isStop(input);

    // Assert
    REQUIRE_FALSE(stop);
}