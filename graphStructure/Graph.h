#pragma once
#include "Node.h"
#include "Edge.h"
#include <bits/stdc++.h>
using namespace std;

class Node;
class Edge;

class Graph{
public:
    bool isDirected, isWeighted;
    int nodeCount;
    vector<Edge> edges;
    set<Node*> nodes;
    map<string, int> ids;
    vector<string> nodeLabels;

    Graph(bool isDirected, bool isWeighted);
    void addNode(Node *node);
    void addEdge(Edge edge);
};



