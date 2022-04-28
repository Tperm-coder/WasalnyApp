#pragma once
#include "Node.h"
#include <bits/stdc++.h>

class Node;

const int N = 1e5 + 7, INF = 1e9;

class Path {
public:
    Node *from, *to;
    vector<Node*> path;
    int shortestDistance;
    vector<pair<Node*, pair<Edge*, int>>> algoPath;

    Path(Node *from, Node *to, vector<Node*> path, int shortestDistance, vector<pair<Node*, pair<Edge*, int>>> algoPath);
};



