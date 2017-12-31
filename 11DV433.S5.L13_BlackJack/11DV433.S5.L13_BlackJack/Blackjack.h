#pragma once

#include "Player.h"

const int MAX_READ_INPUT_LENGTH = 100;

void blackjack();

void setup(Player *& players, int & numberOfPlayers, int & markersPerPlayer, int *& cards, int & numberOfCards);

unsigned int getIntegerFromUser(const char *question);

void setupPlayers(Player *& players, int numberOfPlayers, int markersPerPlayer);

void getShuffledDeck(int *& cards, int & numberOfCards);

void shuffleDeck(int *& cards, int & numberOfCards);

bool userYesOrNo(const char *question);

void placeBets(Player *& players, int numberOfPlayers);

void placeBet(Player & player);

void dealCards(Player *& players, int & numberOfPlayers, int *& dealerCards, int & numberOfDealerCards, int *& cards, int & numberOfCards);

void dealCard(int *& receiverCards, int & numberOfReceiverCards, int *& cards, int & numberOfCards);

void push(int card, int *& cards, int & numberOfCards);

int pop(int *& cards, int & numberOfCards);

void play(Player *& players, int & numberOfPlayers, int *& dealerCards, int & numberOfDealerCards, int *& cards, int & numberOfCards);

int calculateWin(int * cards, int numberOfCards, int bet, int dealerScore, int numberOfDelaerCards);

void deletePlayer(Player *& players, int & numberOfPlayers, int playerIndex);

void printTable(Player *& players, int & numberOfPlayers, int *& dealerCards, int numberOfDealerCards, int activePlayer, bool printOnlyFirstDealerCard = true, bool printScore = false);

void printDealerCards(int *& dealerCards, int numberOfDealerCards, bool printOnlyFirstDealerCard, int middlePosition);

void printPlayerCards(Player *& players, int & numberOfPlayers, int activePlayer, int columnWidth);

void printScore(Player *& players, int numberOfPlayers, int columnWidth);

int bestValue(int *& cards, int & numberOfCards);

int getRank(int card);

void getCard(int card, char *outCard);