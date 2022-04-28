#include "Path.h"
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

Path* Bellman(Node *from, Node *to, Graph *graph) {
    vector<Node*> parent(N);
    vector<int> cost(N, INF);
    vector<pair<Node*, pair<Edge*, int>>> algoPath;

    cost[from->id] = 0;
    parent[from->id] = NULL;

    for (int node = 0; node < graph->nodeCount - 1; node++) {
        for (auto edge: graph->edges) {
            int newCost = cost[edge.first.from->id] + edge.first.weight;
            if (newCost < cost[edge.first.to->id]) {
                cost[edge.first.to->id] = newCost;
                parent[edge.first.to->id] = edge.first.from;
                algoPath.push_back({NULL, {edge.second, newCost}});
            }
        }
    }

    vector<Node*> path;
    Node *curNode = to;
    while (parent[curNode->id] != NULL) {
        path.push_back(curNode);
        curNode = parent[curNode->id];
    }
    path.push_back(from);
    reverse(path.begin(), path.end());

    if (cost[to->id] == INF)
        cost[to->id] = -1;

    return new Path(from, to, path, cost[to->id], algoPath);
}

