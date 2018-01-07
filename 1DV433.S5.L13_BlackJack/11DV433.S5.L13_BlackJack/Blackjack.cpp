//-----------------------------------------------------------------------
// File:    Blackjack.cpp
// Summary: Blackjack game
// Version: 1.1
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------
// Log:   2017-12-30 File created by Christoffer. Initial version only
//                   available for Windows.
//        2018-01-07 Version 1.1. Bug fix.
//-----------------------------------------------------------------------

// Preprocessor directives
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <Windows.h>
#include "Blackjack.h"

using namespace std;

const int NUMBER_OF_CARDS_IN_DECK = 52;
const int BLACKJACK = 21;

//-----------------------------------------------------------------
// void blackjack()
//
// Summary: A game of blackjack
// Returns: -
//-----------------------------------------------------------------
void blackjack()
{
    // Enable memory leak flags
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    do
    {
        int numberOfPlayers;
        Player *players = nullptr;
        int markersPerPlayer;
        int numberOfCards;
        int *cards = nullptr;
        int *dealerCards = nullptr;;
        int numberOfDealerCards = 0;

        // Setup all needed input
        setup(players, numberOfPlayers, markersPerPlayer, cards, numberOfCards);

        // Play while there are still players and those want to ccontinue playing
        do
        {
            placeBets(players, numberOfPlayers);
            dealCards(players, numberOfPlayers, dealerCards, numberOfDealerCards, cards, numberOfCards);
            play(players, numberOfPlayers, dealerCards, numberOfDealerCards, cards, numberOfCards);
        } while (numberOfPlayers > 0 && userYesOrNo("One more round?"));

        // Explain why the game ended
        if (numberOfPlayers == 0)
        {
            cout << "All players were eliminated." << endl;
        }

        // Cleanup
        delete[] cards;
        delete[] dealerCards;
        delete[] players;
    } while (userYesOrNo("One more game?"));
}

//-----------------------------------------------------------------
// void setup(Player *&players, int &numberOfPlayers, int &markersPerPlayer, int *&cards, int &numberOfCards)
//
// Summary: Prepare the players and deck needed to play
// Returns: -
//-----------------------------------------------------------------
void setup(Player *&players, int &numberOfPlayers, int &markersPerPlayer, int *&cards, int &numberOfCards)
{
    numberOfPlayers = getIntegerFromUser("How many players?");

    markersPerPlayer = getIntegerFromUser("How many markers per player?");

    // Create players and give the their markers
    setupPlayers(players, numberOfPlayers, markersPerPlayer);

    // Setup the deck that is to be used
    unsigned int numberOfDecks =  getIntegerFromUser("How many decks are to be used?");
    numberOfCards = numberOfDecks * NUMBER_OF_CARDS_IN_DECK;
    getShuffledDeck(cards, numberOfCards);
}

//-----------------------------------------------------------------
// unsigned int getIntegerFromUser(const char *question)
//
// Summary: Poses a question to the user and returns the answer as an integer
// Returns: A positive integer
//-----------------------------------------------------------------
unsigned int getIntegerFromUser(const char *question)
{
    unsigned int value;

    while (true)
    {
        // Pose question and read answer
        cout << question << ": ";
        cin >> value;

        if (cin.fail())
        {
            // Explain what went wrong
            cout << "Invalid input. Please enter a positive integer." << endl;
            // Clear error
            cin.clear();
            // Clear input (this has to be done after error clearing)
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
        }
        else
        {
            // Clear input 
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
            return value;
        }
    }
}

//-----------------------------------------------------------------
// void setupPlayers(Player *&players, int numberOfPlayers, int markersPerPlayer)
//
// Summary: Creates players and assigns markers and identifying number
// Returns: -
//-----------------------------------------------------------------
void setupPlayers(Player *&players, int numberOfPlayers, int markersPerPlayer)
{
    try
    {
        players = new Player[numberOfPlayers];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Assign markers and id to each player
    for (int i = 0; i < numberOfPlayers; i++)
    {
        players[i].id = i + 1;
        players[i].markers = markersPerPlayer;
    }
}

//-----------------------------------------------------------------
// void getShuffledDeck(int *&cards, int &numberOfCards)
//
// Summary: Populates the deck and allows the user to shuffle it
// Returns: -
//-----------------------------------------------------------------
void getShuffledDeck(int *&cards, int &numberOfCards)
{
    try
    {
        cards = new int[numberOfCards];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Assign values to each card
    for (int i = 0; i < numberOfCards; i++) {
        cards[i] = i + 1;
    }

    // Allow the user to choose how many times the deck should be shuffled
    do
    {
        cout << "Shuffling ..." << endl;
        shuffleDeck(cards, numberOfCards);
    } while (userYesOrNo("Shuffle one more time?"));
}

//-----------------------------------------------------------------
// void shuffleDeck(int *&cards, int &numberOfCards)
//
// Summary: Emulates shuffling of the deck
// Returns: -
//-----------------------------------------------------------------
void shuffleDeck(int *&cards, int &numberOfCards)
{
    // Seed random number generator
    srand(time(NULL));

    // Split deck somewhere in the two middle quartiles
    int firstPartSize = numberOfCards / 4 + rand() % (numberOfCards / 2);
    int secondPartSize = numberOfCards - firstPartSize;

    // Create two arrays to hold the cards while shuffling
    int *firstDeckPart;
    int *secondDeckPart;
    try
    {
        firstDeckPart = new int[firstPartSize];
        secondDeckPart = new int[secondPartSize];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Put first half of deck in first array
    int i;
    for (i = 0; i < firstPartSize; i++)
    {
        firstDeckPart[i] = cards[i];
    }

    // Put second half of deck in second array
    for (int j = 0; j < secondPartSize; i++, j++)
    {
        secondDeckPart[j] = cards[i];
    }

    // Shuffle
    for (int deckIndex = 0, partOneIndex = 0, partTwoIndex = 0; deckIndex < numberOfCards; deckIndex++)
    {
        // Get a random 0 or 1
        bool random = rand() % 2 - 1;

        // If random is 1, use card from 1 array if possible
        if ((random && partOneIndex < firstPartSize) || partTwoIndex >= secondPartSize)
        {
            cards[deckIndex] = firstDeckPart[partOneIndex++];
        }
        else
        {
            cards[deckIndex] = secondDeckPart[partTwoIndex++];
        }
    }

    // Cleanup
    delete[] firstDeckPart;
    delete[] secondDeckPart;
}

//-----------------------------------------------------------------
// bool userYesOrNo(char *question)
//
// Summary: Asks the user the supplied question.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------
bool userYesOrNo(const char *question)
{
    char input[MAX_READ_INPUT_LENGTH];

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    cin.getline(input, MAX_READ_INPUT_LENGTH);
    cout << endl;

    // Check if answer is negative
    auto answer = toupper(input[0]) != 'N';

    return answer;
}

//-----------------------------------------------------------------
// void placeBets(Player *&players, int numberOfPlayers)
//
// Summary: Asks each user how much to bet
// Returns: -
//-----------------------------------------------------------------
void placeBets(Player *&players, int numberOfPlayers)
{
    for (int i = 0; i < numberOfPlayers; i++)
    {
        placeBet(players[i]);
    }
}

//-----------------------------------------------------------------
// void placeBet(Player &player)
//
// Summary: Asks user how much to bet
// Returns: -
//-----------------------------------------------------------------
void placeBet(Player &player)
{
    while (true)
    {
        // Ask user how much to bet
        cout << "Player " << player.id << endl;
        int bet = getIntegerFromUser("How much markers to bet?");

        // Make sure user has enough markers
        if (bet > player.markers)
        {
            cout << "Player only has " << player.markers << endl;
        }
        else
        {
            // Move markers from markers to bet
            player.bet = bet;
            player.markers -= bet;
            return;
        }
    }
}

//-----------------------------------------------------------------
// void dealCards(Player *&players, int &numberOfPlayers, int *&dealerCards, int &numberOfDealerCards, int *&cards, int &numberOfCards)
//
// Summary: Deal players and dealer 2 cards each
// Returns: -
//-----------------------------------------------------------------
void dealCards(Player *&players, int &numberOfPlayers, int *&dealerCards, int &numberOfDealerCards, int *&cards, int &numberOfCards)
{
    const int NUMBER_OF_CARDS = 2;
    for (int i = 0; i < NUMBER_OF_CARDS; i++)
    {
        // Deal one card to each player
        for (int j = 0; j < numberOfPlayers; j++)
        {
            dealCard(players[j].cards, players[j].numberOfCards, cards, numberOfCards);
        }

        // Deal one card to the dealer
        dealCard(dealerCards, numberOfDealerCards, cards, numberOfCards);
    }
}

//-----------------------------------------------------------------
// void dealCard(int *&receiverCards, int &numberOfReceiverCards, int *&cards, int &numberOfCards)
//
// Summary: Takes a card from the top of the deck and gives it to the receiver
// Returns: -
//-----------------------------------------------------------------
void dealCard(int *&receiverCards, int &numberOfReceiverCards, int *&cards, int &numberOfCards)
{
    // Make sure that there are cards in the deck
    if (numberOfCards <= 0)
    {
        cout << "Dealer is out of cards. Adding new deck ..." << endl;
        delete[] cards;
        numberOfCards = NUMBER_OF_CARDS_IN_DECK;
        getShuffledDeck(cards, numberOfCards);
    }

    // Take card from top of deck
    int card = pop(cards, numberOfCards);

    // Give it to the receiver
    push(card, receiverCards, numberOfReceiverCards);
}

//-----------------------------------------------------------------
// void push(int card, int *&cards, int &numberOfCards)
//
// Summary: Place the card at the beginning of the array
// Returns: -
//-----------------------------------------------------------------
void push(int card, int *&cards, int &numberOfCards)
{
    // Create temp variables
    int *newArray;
    const int NEW_SIZE = numberOfCards + 1;

    try
    {
        // Allocate memory
        newArray = new int[NEW_SIZE];
    }
    catch (bad_alloc)
    {
        // Explain the issue and the terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Place the card first
    newArray[0] = card;

    // Copy all values from the old array to the new array
    for (int i = 0; i < numberOfCards; i++)
    {
        newArray[i + 1] = cards[i];
    }

    // Cleanup old array
    if (cards != nullptr)
    {
        delete[] cards;
    }

    // Point old to the temp values
    cards = newArray;
    numberOfCards = NEW_SIZE;
}

//-----------------------------------------------------------------
// int pop(int *&cards, int &numberOfCards)
//
// Summary: Removes the first card from the array
// Returns: The card as an integer
//-----------------------------------------------------------------
int pop(int *&cards, int &numberOfCards)
{
    // Create temp variables
    int *newArray;
    const int NEW_SIZE = numberOfCards - 1;

    if (NEW_SIZE > 0)
    {
        try
        {
            // Allocate memory
            newArray = new int[NEW_SIZE];
        }
        catch (bad_alloc)
        {
            // Explain the issue and the terminate with error code 1
            cout << "Failed to allocate memory. Exiting ..." << endl;
            exit(1);
        }

        // Copy all values from the old array to the new array
        for (int i = 0; i < NEW_SIZE; i++)
        {
            newArray[i] = cards[i + 1];
        }
    }
    else
    {
        newArray = nullptr;
    }

    // Take the first card
    const int POPPED = cards[0];

    // Cleanup
    delete[] cards;

    // Point old to the temp values
    cards = newArray;
    numberOfCards = NEW_SIZE;

    return POPPED;
}

//-----------------------------------------------------------------
// void play(Player *&players, int &numberOfPlayers, int *&dealerCards, int &numberOfDealerCards, int *&cards, int &numberOfCards)
//
// Summary: The game play
// Returns: -
//-----------------------------------------------------------------
void play(Player *&players, int &numberOfPlayers, int *&dealerCards, int &numberOfDealerCards, int *&cards, int &numberOfCards)
{
    // Let all players choose how many cards to take
    for (int i = 0; i < numberOfPlayers; i++)
    {
        printTable(players, numberOfPlayers, dealerCards, numberOfDealerCards, i);

        while (bestValue(players[i].cards, players[i].numberOfCards) < BLACKJACK && userYesOrNo("Hit?"))
        {
            dealCard(players[i].cards, players[i].numberOfCards, cards, numberOfCards);
            printTable(players, numberOfPlayers, dealerCards, numberOfDealerCards, i);
        }
    }

    // Deal cards to dealer until at least 17
    int dealerScore = bestValue(dealerCards, numberOfDealerCards);
    const int DEALER_STOP_SCORE = 17;
    while (dealerScore < DEALER_STOP_SCORE)
    {
        dealCard(dealerCards, numberOfDealerCards, cards, numberOfCards);
        dealerScore = bestValue(dealerCards, numberOfDealerCards);
    }

    // Calculate how much each player win
    for (int i = 0; i < numberOfPlayers; i++)
    {
        players[i].win = calculateWin(players[i].cards, players[i].numberOfCards, players[i].bet, dealerScore, numberOfDealerCards);
        players[i].markers += players[i].win;
    }

    // Print the table with the round score
    printTable(players, numberOfPlayers, dealerCards, numberOfDealerCards, -1, false, true);

    // Cleanup
    delete[] dealerCards;
    dealerCards = nullptr;
    numberOfDealerCards = 0;

    // Delete player if out of markers and otherwise prepare it for next round
    int i = 0;
    while (i < numberOfPlayers)
    {
        if (players[i].markers == 0)
        {
            cout << endl << "Player " << players[i].id << " was eliminated." << endl;
            deletePlayer(players, numberOfPlayers, i);
        }
        else
        {
            players[i].prepareNewRound();
            i++;
        }
    }
}

//-----------------------------------------------------------------
// int calculateWin(int *cards, int numberOfCards, int bet, int dealerScore, int numberOfDealerCards)
//
// Summary: Calculates if and how much the player win
// Returns: Win as integer
//-----------------------------------------------------------------
int calculateWin(int *cards, int numberOfCards, int bet, int dealerScore, int numberOfDealerCards)
{
    int const DRAW_LIMIT = 20;
    int const PLAYER_SCORE = bestValue(cards, numberOfCards);

    // Calculate win
    if (PLAYER_SCORE <= BLACKJACK)
    {
        if (dealerScore < PLAYER_SCORE || dealerScore > BLACKJACK)
        {
            if (PLAYER_SCORE == BLACKJACK && numberOfCards == 2)
            {
                return bet * 1.5; // Blackjack
            }
            else
            {
                return bet * 2; // Player beat dealer
            }
        }
        else if (dealerScore == PLAYER_SCORE)
        {
            if (dealerScore < DRAW_LIMIT)
            {
                return 0; // Dealer wins draw lower than 20
            }
            else if (dealerScore == BLACKJACK && numberOfDealerCards > 2 && numberOfCards == 2)
            {
                return 1.5 * bet; // Player blackjack beats dealer 21
            }
            else
            {
                return bet; // Draw yields the money back
            }
        }
        else
        {
            return 0; // Dealer beats player
        }
    }
    else
    {
        return 0; // Player goes over 21
    }
}

//-----------------------------------------------------------------
// void deletePlayer(Player *&players, int &numberOfPlayers, int playerIndex)
//
// Summary: Deletes player from player array
// Returns: -
//-----------------------------------------------------------------
void deletePlayer(Player *&players, int &numberOfPlayers, int playerIndex)
{
    // Create temp array
    Player *newPlayers;
    try
    {
        newPlayers = new Player[numberOfPlayers - 1];
    }
    catch (bad_alloc)
    {
        // Explain the issue and then terminate with error code 1
        cout << "Failed to allocate memory. Exiting ..." << endl;
        exit(1);
    }

    // Copy players to the new array
    for (int newIndex = 0, oldIndex = 0; oldIndex < numberOfPlayers; oldIndex++)
    {
        if (oldIndex != playerIndex)
        {
            newPlayers[newIndex] = players[oldIndex];
            newIndex++;
        }
    }

    numberOfPlayers--;

    // Free memory
    delete[] players;

    // Point array to the new array
    players = newPlayers;
}

//-----------------------------------------------------------------
// void printTable(Player *&players, int &numberOfPlayers, int *&dealerCards, int numberOfDealerCards, int activePlayer, bool printOnlyFirstDealerCard, bool printRoundScore)
//
// Summary: Prints the whole table
// Returns: -
//-----------------------------------------------------------------
void printTable(Player *&players, int &numberOfPlayers, int *&dealerCards, int numberOfDealerCards, int activePlayer, bool printOnlyFirstDealerCard, bool printRoundScore)
{
    // Clear the screen
    system("cls");

    const int COLUMN_WIDTH = 9;
    const int MIDDLE = COLUMN_WIDTH * numberOfPlayers / 2;
    const int MAX_CARD_STRING_LENGTH = 4;

    // Print dealer cards in the middle
    printDealerCards(dealerCards, numberOfDealerCards, printOnlyFirstDealerCard, MIDDLE, MAX_CARD_STRING_LENGTH);

    // Print the player cards
    printPlayerCards(players, numberOfPlayers, activePlayer, COLUMN_WIDTH, MAX_CARD_STRING_LENGTH);

    // Print the current score if wanted
    if (printRoundScore)
    {
        printScore(players, numberOfPlayers, COLUMN_WIDTH);
    }
}

//-----------------------------------------------------------------
// void printDealerCards(int *&dealerCards, int numberOfDealerCards, bool printOnlyFirstDealerCard, int middlePosition)
//
// Summary: Prints the dealer cards
// Returns: -
//-----------------------------------------------------------------
void printDealerCards(int *&dealerCards, int numberOfDealerCards, bool printOnlyFirstDealerCard, const int MIDDLE_POSITION, const int MAX_CARD_STRING_LENGTH)
{
    cout << setw(MIDDLE_POSITION) << "Dealer" << endl;

    // Print the cards
    int cardIndex = 0;
    do
    {
        char *card = new char[MAX_CARD_STRING_LENGTH];
        getCard(dealerCards[cardIndex++], card, MAX_CARD_STRING_LENGTH);
        cout << setw(MIDDLE_POSITION) << card << endl;
        delete[] card;
    } while (!printOnlyFirstDealerCard && cardIndex < numberOfDealerCards);

    cout << endl;
}

//-----------------------------------------------------------------
// void printPlayerCards(Player *&players, int &numberOfPlayers, int activePlayer, int columnWidth)
//
// Summary: Prints the players cards
// Returns: -
//-----------------------------------------------------------------
void printPlayerCards(Player *&players, int &numberOfPlayers, int activePlayer, const int COLUMN_WIDTH, const int MAX_CARD_STRING_LENGTH)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int YELLOW = 14;
    const int WHITE = 15;
    // Print player identifier
    const char *PLAYER_STRING = " Player";
    const int SPACE_LEFT_FOR_NUMBER = COLUMN_WIDTH - strlen(PLAYER_STRING);
    for (int i = numberOfPlayers - 1; i >= 0; i--)
    {
        cout << PLAYER_STRING << setw(SPACE_LEFT_FOR_NUMBER) << players[i].id;
    }
    cout << endl;

    // Print cards
    int cardIndex = 0;
    bool allCardsPrinted;
    do
    {
        allCardsPrinted = true;
        for (int i = numberOfPlayers - 1; i >= 0; i--)
        {
            // Check if there are more cards after the current
            if (players[i].numberOfCards > (cardIndex + 1))
            {
                allCardsPrinted = false;
            }

            // Get the card as a string
            char output[4];
            if (players[i].numberOfCards > cardIndex)
            {
                getCard(players[i].cards[cardIndex], output, MAX_CARD_STRING_LENGTH);
            }
            else
            {
                // No card is an empty string
                strcpy_s(output, sizeof output, "");
            }

            // Print card
            if (i == activePlayer)
            {
                // Print cards as yellow to inform the user which the current player is
                SetConsoleTextAttribute(hConsole, YELLOW);
                cout << setw(COLUMN_WIDTH) << output;
                SetConsoleTextAttribute(hConsole, WHITE);
            }
            else
            {
                cout << setw(COLUMN_WIDTH) << output;
            }
        }

        cout << endl;
        cardIndex++;
    } while (!allCardsPrinted);

    cout << endl;
}

//-----------------------------------------------------------------
// void printScore(Player *&players, int numberOfPlayers, int columnWidth)
//
// Summary: Prints the players score
// Returns: -
//-----------------------------------------------------------------
void printScore(Player *&players, int numberOfPlayers, int columnWidth)
{
    const char *WIN_STRING = " Win:";
    const int SPACE_LEFT_FOR_WIN = columnWidth = strlen(WIN_STRING);
    const char *TOT_STRING = " Tot:";
    const int SPACE_LEFT_FOR_TOT = columnWidth = strlen(TOT_STRING);

    // Print win
    for (int i = numberOfPlayers - 1; i >= 0; i--)
    {
        cout << WIN_STRING << setw(SPACE_LEFT_FOR_WIN) << players[i].win;
    }

    cout << endl;

    // Print markers
    for (int i = numberOfPlayers - 1; i >= 0; i--)
    {
        cout << TOT_STRING << setw(SPACE_LEFT_FOR_TOT) << players[i].markers;
    }

    cout << endl;
}

//-----------------------------------------------------------------
// int bestValue(int *&cards, int &numberOfCards)
//
// Summary: Calculates the best value for a set of cards (closest
//          to but lower or equal to 21)
// Returns: The value as an integer
//-----------------------------------------------------------------
int bestValue(int *&cards, int &numberOfCards)
{
    int total = 0;
    int aces = 0;

    // Calculate the sum and the number of aces
    for (int i = 0; i < numberOfCards; i++)
    {
        int rank = getRank(cards[i]);
        total += rank;

        if (rank == 11)
        {
            aces++;
        }
    }

    // Convert aces from 11 to 1 if needed
    while (total > BLACKJACK && aces > 0)
    {
        total -= 10;
        aces--;
    }

    return total;
}

//-----------------------------------------------------------------
// int getRank(int card)
//
// Summary: Calculates the rank (value) for a card
// Returns: The value as an integer
//-----------------------------------------------------------------
int getRank(int card)
{
    int rank = card % 13;

    if (rank < 1) // King
    {
        return 10;
    }
    else if (rank < 2) // Ace
    {
        return 11;
    }
    else if (rank < 11) // 2-10
    {
        return rank;
    }
    else // Jack and Queen
    {
        return 10;
    }
}

//-----------------------------------------------------------------
// void getCard(int card, char *outCard)
//
// Summary: Converts the card integer value to a string. The string
//          outCard has to be able to hold at least 4 char
// Returns: -
//-----------------------------------------------------------------
void getCard(int card, char *outCard, const int MAX_CARD_STRING_LENGTH)
{
    // Suit
    switch (card % 4)
    {
    case 0:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "S"); // Spades
        break;
    case 1:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "C"); // Club
        break;
    case 2:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "H"); // Heart
        break;
    case 3:
        strcpy_s(outCard, MAX_CARD_STRING_LENGTH, "D"); // Diamond
        break;
    }

    // Rank
    const int VALUE = card % 13;
    switch (VALUE)
    {
    case 0:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "K");
        break;
    case 1:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, " ");
        break;
    case 11:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "J");
        break;
    case 12:
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, "Q");
        break;
    default:
        int const MAX_RANK_LENGTH = 3;
        char temp[MAX_RANK_LENGTH];
        _itoa_s(VALUE, temp, MAX_RANK_LENGTH, 10);
        strcat_s(outCard, MAX_CARD_STRING_LENGTH, temp);
        break;
    }
}