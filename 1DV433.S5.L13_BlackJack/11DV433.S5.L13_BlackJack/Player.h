#pragma once
class Player
{
private:
    void swap(Player & first, Player & second);

public:
    int id;
    int *cards;
    int numberOfCards;
    int markers;
    int bet;
    int win;

    Player();
    Player(Player & other);
    Player& operator=(Player other);
    void prepareNewRound();
    virtual ~Player();
};