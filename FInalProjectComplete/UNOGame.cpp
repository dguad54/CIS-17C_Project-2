#include "UNOGame.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

UNOGame::UNOGame() {
    currentPlayer = 0;
    currentNode = gameTree.getRoot();
    reverse = false;
    initializeDeck();
    initializePlayers();
}

size_t UNOGame::hashFunction(const string& key) {
    size_t hash = 0;
    for (char c : key) {
        hash += c;
    }
    return hash;
}

void UNOGame::initializeDeck() {
    vector<string> colors = { "Red", "Blue", "Green", "Yellow" };
    vector<string> values = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Skip", "Reverse", "Draw Two" };
    for (const string& color : colors) {
        for (const string& value : values) {
            Card card;
            card.color = color;
            card.value = value;
            deck.push_back(card);
        }
    }
    for (int i = 0; i < 4; i++) {
        Card wildCard;
        wildCard.color = "Wild";
        wildCard.value = "Wild";
        deck.push_back(wildCard);

        Card wildDrawFourCard;
        wildDrawFourCard.color = "Wild";
        wildDrawFourCard.value = "Wild Draw Four";
        deck.push_back(wildDrawFourCard);
    }
}

void UNOGame::initializePlayers() {
    int numPlayers;
    cout << "Enter the number of players: ";
    cin >> numPlayers;

    for (int i = 1; i <= numPlayers; i++) {
        string playerName;
        cout << "Enter player " << i << " name:" << endl;
        cin >> playerName;
        players[playerName] = 0;
    }
}

void UNOGame::shuffleDeck() {
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

void UNOGame::dealCards() {
    for (auto& player : players) {
        for (int i = 0; i < 7; i++) {
            playerCards[player.first].push_back(deck.back());
            deck.pop_back();
        }
    }
}

void UNOGame::displayHand(const string& playerName) {
    cout << playerName << "'s Hand: ";
    for (const Card& card : playerCards[playerName]) {
        cout << "[" << card.color << " " << card.value << "] ";
    }
    cout << endl;
}

bool UNOGame::hasValidMove(const string& playerName) {
    for (const Card& card : playerCards[playerName]) {
        if (isValidMove(card)) {
            return true;
        }
    }
    return false;
}

bool UNOGame::isValidMove(const Card& card) {
    const Card& topCard = discardPile.back();
    if (card.color == "Wild" || card.color == topCard.color || card.value == topCard.value) {
        return true;
    }
    return false;
}

void UNOGame::updateCurrentPlayer() {
    int numPlayers = players.size();
    if (reverse) {
        currentPlayer--;
        if (currentPlayer < 0) {
            currentPlayer = numPlayers - 1;
        }
    }
    else {
        currentPlayer++;
        if (currentPlayer >= numPlayers) {
            currentPlayer = 0;
        }
    }
}

void UNOGame::playTurn() {
    const string& currentPlayerName = getPlayerName(currentPlayer);
    cout << "Current Player: " << currentPlayerName << endl;
    displayHand(currentPlayerName);

    bool validMove = false;
    while (!validMove) {
        int cardIndex;
        cout << "Enter the index of the card to play (0-" << playerCards[currentPlayerName].size() - 1 << "): ";
        cin >> cardIndex;

        if (cardIndex >= 0 && cardIndex < playerCards[currentPlayerName].size()) {
            const Card& selectedCard = playerCards[currentPlayerName][cardIndex];
            if (isValidMove(selectedCard)) {
                discardPile.push_back(selectedCard);
                playerCards[currentPlayerName].erase(playerCards[currentPlayerName].begin() + cardIndex);
                validMove = true;
                updateScore(currentPlayerName, selectedCard);
                cout << currentPlayerName << " played [" << selectedCard.color << " " << selectedCard.value << "]" << endl;

                if (playerCards[currentPlayerName].empty()) {
                    cout << currentPlayerName << " has no cards left. They win!" << endl;
                    currentNode->children.push_back(gameTree.createNode(currentPlayerName));
                    return;
                }

                if (selectedCard.value == "Reverse") {
                    reverse = !reverse;
                }
                else if (selectedCard.value == "Skip") {
                    updateCurrentPlayer();
                }
                else if (selectedCard.value == "Draw Two") {
                    string nextPlayer = getNextPlayer();
                    drawCards(nextPlayer, 2);
                }
                else if (selectedCard.value == "Wild Draw Four") {
                    string nextPlayer = getNextPlayer();
                    drawCards(nextPlayer, 4);
                }
                else if (selectedCard.color == "Wild") {
                    string newColor;
                    cout << "Enter the new color (Red, Blue, Green, Yellow): ";
                    cin >> newColor;
                    selectedCard.color == newColor;
                }

                string nextPlayer = getNextPlayer();
                currentNode->children.push_back(gameTree.createNode(nextPlayer));
                currentNode = currentNode->children.back();
                return;
            }
            else {
                cout << "Invalid move. Please select a valid card." << endl;
            }
        }
        else {
            cout << "Invalid index. Please select a valid card." << endl;
        }
    }
}

void UNOGame::updateScore(const string& playerName, const Card& card) {
    int& score = players[playerName];
    if (card.color == "Wild" || card.color == "Wild Draw Four") {
        score += 50;
    }
    else if (card.value == "Draw Two" || card.value == "Reverse" || card.value == "Skip") {
        score += 20;
    }
    else {
        score += stoi(card.value);
    }
}

void UNOGame::drawCards(const string& playerName, int numCards) {
    for (int i = 0; i < numCards; i++) {
        playerCards[playerName].push_back(deck.back());
        deck.pop_back();
    }
}

string UNOGame::getNextPlayer() {
    int numPlayers = players.size();
    int nextPlayer;
    if (reverse) {
        nextPlayer = currentPlayer - 1;
        if (nextPlayer < 0) {
            nextPlayer = numPlayers - 1;
        }
    }
    else {
        nextPlayer = currentPlayer + 1;
        if (nextPlayer >= numPlayers) {
            nextPlayer = 0;
        }
    }
    return getPlayerName(nextPlayer);
}

string UNOGame::getPlayerName(int playerIndex) {
    for (const auto& player : players) {
        if (player.second == playerIndex) {
            return player.first;
        }
    }
    return "";
}

void UNOGame::playGame() {
    shuffleDeck();
    dealCards();

    std::cout << "Game Started!" << std::endl;

    while (true) {
        string currentPlayerName = getPlayerName(currentPlayer);
        cout << "------------------------" << endl;
        cout << "Current Player: " << currentPlayerName << endl;
        displayHand(currentPlayerName);

        if (!hasValidMove(currentPlayerName)) {
            cout << "No valid moves. Drawing a card..." << endl;
            drawCards(currentPlayerName, 1);
            displayHand(currentPlayerName);
        }

        playTurn();
        updateCurrentPlayer();

        cout << "------------------------" << endl;
        cout << "Scores:" << endl;
        for (const auto& player : players) {
            cout << player.first << ": " << player.second << endl;
        }
        cout << "------------------------" << endl;
    }
}
