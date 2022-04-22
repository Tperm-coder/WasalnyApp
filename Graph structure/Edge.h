#pragma once
#include "Node.h"
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;
class Node;

class Edge{
public:
    Node *from, *to;
    int weight;
    Edge(Node *from, Node *to);
    Edge(Node *from, Node *to, int weight);
};
