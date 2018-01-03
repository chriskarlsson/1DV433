#include <cstring>
#include "Soundex.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Not adding numbers twice", "[encodeSoundex]")
{
    // Arrange
    const char *name = "Svennshonn";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "S152");
}

TEST_CASE("Only encoding expected charcters", "[encodeSoundex]")
{
    // Arrange
    const char *name = "Eva";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "E100");
}

TEST_CASE("Empty string", "[encodeSoundex]")
{
    // Arrange
    const char *name = "";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "0000");
}

TEST_CASE("Invalid first character", "[encodeSoundex]")
{
    // Arrange
    const char *name = "3r1c";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "0000");
}

TEST_CASE("Later invalid characters ignored", "[encodeSoundex]")
{
    // Arrange
    const char *name = "B3n";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "B500");
}

TEST_CASE("Non alphanumeric characters ignored", "[encodeSoundex]")
{
    // Arrange
    const char *name = "J@mes";
    char soundex[SOUNDEX_LENGTH + 1];

    // Act
    encodeSoundex(name, soundex);

    // Assert
    REQUIRE_FALSE(soundex == "J520");
}