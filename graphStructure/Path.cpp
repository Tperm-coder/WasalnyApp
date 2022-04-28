#include "Path.h"
#include <bits/stdc++.h>
using namespace std;

Path::Path(Node *from, Node *to, vector<Node*> path, int shortestDistance) {
    this->from = from;
    this->to = to;
    this->path = path;
    this->shortestDistance = shortestDistance;
}

