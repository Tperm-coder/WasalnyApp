#pragma once
#include "Edge.h"
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int id;
    string label;
    set<pair<Node*, int>> links;

    Node(string label);
};