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
    set<Node*> nodes;
    vector<Edge> edges;
    map<string, int> ids;
    vector<string> nodeLabels;
    bool isDirected, isWeighted;

    Graph(bool isDirected, bool isWeighted);
    void addNode(Node *node);
    void addEdge(Edge edge);
};



