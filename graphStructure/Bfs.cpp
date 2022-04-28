#include "Path.h"
#include <bits/stdc++.h>
using namespace std;

Path* Bfs(Node *from, Node *to) {
    queue<Node*> q;
    vector<Node*> parent(N);
    vector<int> cost(N, INF);

    q.push(from);
    cost[from->id] = 0;
    parent[from->id] = NULL;

    while(q.size())
    {
        auto curNode = q.front();
        int curNodeId = curNode->id;
        int curNodeCost = cost[curNodeId];

        set<pair<Node*, int>>::iterator nextNode;

        q.pop();

        for(nextNode = curNode->links.begin(); nextNode != curNode->links.end(); nextNode++)
        {
            int nextNodeCost = curNodeCost + 1;
            int nextNodeId = nextNode->first->id;

            if(nextNodeCost < cost[nextNodeId])
            {
                parent[nextNodeId] = curNode;
                cost[nextNodeId] = nextNodeCost;
                q.emplace(nextNode->first);
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

