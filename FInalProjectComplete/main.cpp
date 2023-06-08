#include "UNOGame.h"
#include "Graph.h"
#include <iostream>
using namespace std;


int main() {
    int input;

    cout << "Welcome to UNO Game!" << endl;
    cout << "Do you wish to view graph traversal? (1 for yes, 0 for no)" << endl;
    cin >> input;
    if (input == 1) {
        Graph unoGraph;

        // Adding UNO cards to the graph using a loop
        vector<string> colors = { "Red", "Green", "Blue" };
        for (const auto& color : colors) {
            vector<UNOCard> cards;
            for (int i = 0; i <= 9; i++) {
                cards.push_back(UNOCard(color, i));
            }
            unoGraph.addEdge(color, cards);
        }

        // Displaying the graph
        cout << "UNO Card Graph:" << endl;
        unoGraph.displayGraph();
        cout << endl;

        // Getting user input for the target card
        string targetColor;
        int targetNumber;

        cout << "Enter the color of the target card: ";
        cin >> targetColor;

        cout << "Enter the number of the target card: ";
        cin >> targetNumber;

        UNOCard targetCard(targetColor, targetNumber);

        // Searching for the user-specified target card using BFS and DFS
        unoGraph.BFS("Red", targetCard);
        unoGraph.DFS("Red", targetCard);
    }
    else {
        cout << "You chose not to view graph traversal." << endl;
    }
    
    UNOGame unoGame;
    unoGame.playGame();

    return 0;
}
