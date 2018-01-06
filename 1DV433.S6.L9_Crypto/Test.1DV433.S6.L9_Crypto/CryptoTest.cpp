#include "Crypto.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Correct conversion of A", "[binaryToChar]")
{
    // Arrange
    const int CHAR_BIT_SIZE = 8;
    char binaryChar[] = "01000001"; // A
    char outChar;

    // Act
    bool result = binaryToChar(binaryChar, CHAR_BIT_SIZE, outChar);

    // Assert
    REQUIRE((result && outChar == 'A'));
}

TEST_CASE("Inital value of char not affecting result", "[binaryToChar]")
{
    // Arrange
    const int CHAR_BIT_SIZE = 8;
    char binaryChar[] = "01000001"; // A
    char outChar = 'B';

    // Act
    bool result = binaryToChar(binaryChar, CHAR_BIT_SIZE, outChar);

    // Assert
    REQUIRE((result && outChar == 'A'));
}

TEST_CASE("Correct conversion of non alphanumeric", "[binaryToChar]")
{
    // Arrange
    const int CHAR_BIT_SIZE = 8;
    char binaryChar[] = "00001010"; // Line feed
    char outChar;

    // Act
    bool result = binaryToChar(binaryChar, CHAR_BIT_SIZE, outChar);

    // Assert
    REQUIRE((result && outChar == '\n'));
}

TEST_CASE("Invalid char yields false", "[binaryToChar]")
{
    // Arrange
    const int CHAR_BIT_SIZE = 8;
    char binaryChar[] = "00000002";
    char outChar;

    // Act
    bool result = binaryToChar(binaryChar, CHAR_BIT_SIZE, outChar);

    // Assert
    REQUIRE_FALSE(result);
}