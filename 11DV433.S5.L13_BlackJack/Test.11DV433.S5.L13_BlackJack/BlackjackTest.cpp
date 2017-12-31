#include "Blackjack.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Closer to 21 doubles the bet", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 8 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 17;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE( win == (bet * 2) );
}

TEST_CASE("Closer to 21 doubles the bet 2", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 8 , 3};
    int numberOfCards = 3;
    int bet = 2;
    int dealerScore = 20;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == (bet * 2));
}

TEST_CASE("Going over 21 gives nothing", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 8 , 4};
    int numberOfCards = 3;
    int bet = 2;
    int dealerScore = 22;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == 0);
}

TEST_CASE("Blackjack closer to 21 gives 1.5 the bet", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 1 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 20;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == (bet * 1.5));
}

TEST_CASE("Blackjack beats 21 and gives 1.5 the bet", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 1 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 21;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == (bet * 1.5));
}

TEST_CASE("Both blackjack is a draw", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 1 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 21;
    int numberOfDealerCards = 2;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == bet);
}

TEST_CASE("Both 21 is a draw", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 10, 1 };
    int numberOfCards = 3;
    int bet = 2;
    int dealerScore = 21;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == bet);
}

TEST_CASE("Both 20 is a draw", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 10 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 20;
    int numberOfDealerCards = 2;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == bet);
}

TEST_CASE("House win if both has 19", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 9 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 19;
    int numberOfDealerCards = 2;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == 0);
}

TEST_CASE("House win if both has 17", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 7 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 17;
    int numberOfDealerCards = 2;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == 0);
}


TEST_CASE("2 times the bet if house is over 21", "[calculateWin]")
{
    // Arrange
    int cards[] = { 10, 5 };
    int numberOfCards = 2;
    int bet = 2;
    int dealerScore = 22;
    int numberOfDealerCards = 3;

    // Act
    int win = calculateWin(cards, numberOfCards, bet, dealerScore, numberOfDealerCards);

    // Assert
    REQUIRE(win == (bet * 2));
}