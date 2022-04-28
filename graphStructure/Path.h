#pragma once
#include "Node.h"
#include <bits/stdc++.h>

class Node;

class Path {
public:
    Node *from, *to;
    vector<Node*> path;
    int shortestDistance;

    Path(Node *from, Node *to, vector<Node*> path, int shortestDistance);
};



