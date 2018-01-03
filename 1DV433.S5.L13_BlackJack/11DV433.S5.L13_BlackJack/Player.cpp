//-----------------------------------------------------------------------
// File:    Player.cpp
// Summary: The representation of a player
// Version: 1.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-30 File created by Christoffer
//-----------------------------------------------------------------------

#include <algorithm>
#include "Player.h"

// Constructor
Player::Player()
{
    numberOfCards = 0;
    cards = nullptr;
}

// Move constuctor
Player::Player(Player & other) : Player()
{
    swap(*this, other);
}

// = operator overload (copy constructor)
Player& Player::operator=(Player other)
{
    // other taken as value and will not affect original player
    swap(*this, other);

    return *this;
}

//-----------------------------------------------------------------
// void Player::swap(Player & first, Player & second)
//
// Summary: Swaps the two players
// Returns: -
//-----------------------------------------------------------------
void Player::swap(Player & first, Player & second)
{
    std::swap(first.id, second.id);
    std::swap(first.cards, second.cards);
    std::swap(first.numberOfCards, second.numberOfCards);
    std::swap(first.markers, second.markers);
    std::swap(first.bet, second.bet);
    std::swap(first.win, second.win);
}

//-----------------------------------------------------------------
// void Player::prepareNewRound()
//
// Summary: Prepare the player for the next round
// Returns: -
//-----------------------------------------------------------------
void Player::prepareNewRound()
{
    delete[] cards;
    cards = nullptr;

    numberOfCards = 0;
}

// Destructor
Player::~Player()
{
    // Free memory of pointer
    delete[] cards;
}
