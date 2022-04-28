#pragma once
#include "Node.h"
#include "Edge.h"
#include <bits/stdc++.h>
using namespace std;

class Node;
class Edge;

class Graph {
public:
    int nodeCount;
    vector<Node*> nodes;
    map<string, int> ids;
    vector<string> nodeLabels;
    bool isDirected, isWeighted;
    vector<pair<Edge, Edge*>> edges;

    Graph(bool isDirected, bool isWeighted);
    Node* addNode(Node *node);
    void addEdge(Edge *edge);
};



