#include <string>
#include "Formatting.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Detecting invalid non ascii", "[isValidName]")
{
    // Arrange
    string name = "aºb";

    // Act
    auto valid = isValidName(name);

    // Assert
    REQUIRE_FALSE(valid);
}

TEST_CASE("Detecting invalid ascii", "[isValidName]")
{
    // Arrange
    string name = "a+b";

    // Act
    auto valid = isValidName(name);

    // Assert
    REQUIRE_FALSE(valid);
}

TEST_CASE("Allowing valid ascii", "[isValidName]")
{
    // Arrange
    string name = "a b\fc\nd\re\tf\vghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Act
    auto valid = isValidName(name);

    // Assert
    REQUIRE(valid);
}

TEST_CASE("Given test case", "[formatName]")
{
    // Arrange
    string name = "   doNaLd vON   Duck    ";

    // Act
    auto formatted = formatName(name);

    // Assert
    REQUIRE(formatted == "Donald Von Duck");
}

TEST_CASE("Correct white space handling", "[formatName]")
{
    // Arrange
    string name = "a b\fc\nd\re\tf\vghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Act
    auto formatted = formatName(name);

    // Assert
    REQUIRE(formatted == "A B C D E F Ghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
}

TEST_CASE("Removing preceeding white spaces", "[formatName]")
{
    // Arrange
    string name = " \f\n\r\t\va";

    // Act
    auto formatted = formatName(name);

    // Assert
    REQUIRE(formatted == "A");
}

TEST_CASE("Removing trailing white spaces", "[formatName]")
{
    // Arrange
    string name = "a \f\n\r\t\v";

    // Act
    auto formatted = formatName(name);

    // Assert
    REQUIRE(formatted == "A");
}

TEST_CASE("Combining multiple white spaces", "[formatName]")
{
    // Arrange
    string name = "a \f\n\r\t\vb";

    // Act
    auto formatted = formatName(name);

    // Assert
    REQUIRE(formatted == "A B");
}