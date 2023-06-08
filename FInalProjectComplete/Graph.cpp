#include "Graph.h"
#include <iostream>
using namespace std;

void Graph::addEdge(const string& vertex, const vector<UNOCard>& cards) {
    adjList[vertex] = cards;
}

void Graph::displayGraph() {
    for (const auto& pair : adjList) {
        const string& vertex = pair.first;
        const vector<UNOCard>& cards = pair.second;

        cout << vertex << ": ";
        for (const auto& card : cards) {
            cout << "[" << card.color << " " << card.number << "] ";
        }
        cout << endl;
    }
}

bool Graph::BFS(const string& startVertex, const UNOCard& targetCard) {
    unordered_map<string, bool> visited;
    queue<string> q;
    q.push(startVertex);
    visited[startVertex] = true;

    while (!q.empty()) {
        string currentVertex = q.front();
        q.pop();

        for (const auto& card : adjList[currentVertex]) {
            if (card.color == targetCard.color && card.number == targetCard.number) {
                cout << "Found card [" << card.color << " " << card.number << "] using BFS!" << endl;
                return true;
            }

            if (!visited[card.color]) {
                q.push(card.color);
                visited[card.color] = true;
            }
        }
    }

    cout << "Card not found using BFS!" << endl;
    return false;
}

bool Graph::DFS(const string& startVertex, const UNOCard& targetCard) {
    unordered_map<string, bool> visited;
    stack<string> s;
    s.push(startVertex);
    visited[startVertex] = true;

    while (!s.empty()) {
        string currentVertex = s.top();
        s.pop();

        for (const auto& card : adjList[currentVertex]) {
            if (card.color == targetCard.color && card.number == targetCard.number) {
                cout << "Found card [" << card.color << " " << card.number << "] using DFS!" << endl;
                return true;
            }

            if (!visited[card.color]) {
                s.push(card.color);
                visited[card.color] = true;
            }
        }
    }

    cout << "Card not found using DFS!" << endl;
    return false;
}
