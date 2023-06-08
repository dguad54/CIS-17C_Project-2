#ifndef UNOGAME_H
#define UNOGAME_H

#include "Tree.h"
#include "Card.h"
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class UNOGame : public Tree {
protected:
    vector<Card> deck;
    vector<Card> discardPile;
    unordered_map<string, int> players;
    int currentPlayer;
    bool reverse;
    unordered_map<string, vector<Card>> playerCards;
    Tree gameTree;
    TreeNode* currentNode;
    size_t hashCard(const Card& card);
public:
    UNOGame();

    size_t hashFunction(const string& key);

    void initializeDeck();

    void initializePlayers();

    void shuffleDeck();

    void dealCards();

    void displayHand(const string& playerName);

    bool hasValidMove(const string& playerName);

    bool isValidMove(const Card& card);

    void updateCurrentPlayer();

    void playTurn();

    void updateScore(const string& playerName, const Card& card);

    void drawCards(const string& playerName, int numCards);

    string getNextPlayer();

    string getPlayerName(int playerIndex);

    void playGame();

    void mergeSort(vector<Card>& cards);
};

#endif  // UNOGAME_H

