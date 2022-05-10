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

void Path::Display() {
    if (shortestDistance == -1) {
        cout << "There is no path from " << from->label << " to " << to->label << '.' << endl;
        return;
    }

    cout << "The shortest distance from " << from->label << " to " << to->label << " is " << shortestDistance << '.' << endl;
    cout << "The shortest path is as follows:" << endl;
    for (auto node: path) {
        cout << node->label;
        if (node != path.back())
            cout << " -> ";
    }
    cout << endl;
}

