#include "Path.h"
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

Path* Bellman(Node *from, Node *to, Graph *graph) {
    vector<Node*> parent(N);
    vector<int> cost(N, INF);

    cost[from->id] = 0;
    parent[from->id] = NULL;

    for (int node = 0; node < graph->nodeCount - 1; node++) {
        for (auto edge: graph->edges) {
            int newCost = cost[edge.from->id] + edge.weight;
            if (newCost < cost[edge.to->id]) {
                cost[edge.to->id] = newCost;
                parent[edge.to->id] = edge.from;
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

    return new Path(from, to, path, cost[to->id]);
}

