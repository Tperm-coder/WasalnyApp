#pragma once
#include <bits/stdc++.h>
using namespace std;

class Node;
class Edge;

class Node {
public:
    int id;
    string label;
    set<pair<Node*, Edge*>> links;

    Node(string label);
    bool operator == (const Node* node);
};