#pragma once
#include <bits/stdc++.h>
using namespace std;
class Node;

class Node{
public:
    int id;
    string label;
    set<pair<Node*, int>> links;

    Node(string label);

    bool operator == (const Node* n);
};