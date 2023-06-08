#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include "UNOCard.h"

using namespace std;

class Graph {
    unordered_map<string, vector<UNOCard>> adjList;

public:
    void addEdge(const string& vertex, const vector<UNOCard>& cards);

    void displayGraph();

    bool BFS(const string& startVertex, const UNOCard& targetCard);

    bool DFS(const string& startVertex, const UNOCard& targetCard);
};

#endif // GRAPH_H
