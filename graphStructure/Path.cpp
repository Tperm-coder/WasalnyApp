#include "Path.h"
#include <bits/stdc++.h>
using namespace std;

Path::Path(Node *from, Node *to, vector<Node*> path, int shortestDistance, vector<pair<Node*, pair<Edge*, int>>> algoPath) {
    this->to = to;
    this->from = from;
    this->path = path;
    this->algoPath = algoPath;
    this->shortestDistance = shortestDistance;
}

