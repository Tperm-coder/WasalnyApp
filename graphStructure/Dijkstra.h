#pragma once
#include "Node.h"
#include "Graph.h"
#include "Edge.h"
#include <bits/stdc++.h>
class Node;
class Edge;
class Graph;
class Dijkstra {
public:
    Dijkstra(Node *from, Node *to);
    int cst[10000];
    int par[10000];
    vector<string> path;
    priority_queue<pair<int,Node*>> pq;
};



