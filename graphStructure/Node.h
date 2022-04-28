#pragma once
#include <bits/stdc++.h>
using namespace std;
class Node;
class Edge;
class Node {
public:
    int id;
    string label;
    set<pair<Node*, int>> links;
    Node(string label);
    bool operator == (const Node* n);
};
//0 1
//3 3
//1 2 3
//2 3 4
//1 3 2