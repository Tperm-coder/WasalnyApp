#include "Dijkstra.h"
#include <bits/stdc++.h>
using namespace std;
Dijkstra::Dijkstra(Node *from, Node *to) {
    memset(cst,'?',sizeof cst);
    pq.push({0,from});
    cst[from->id] = 0;
    par[from->id] = -1;
    while(!pq.empty())
    {
        auto curNode = pq.top();
        string curNodeName = curNode.second->label;
        int curNodeId = curNode.second->id;
        int curNodeCost = -curNode.first;
        set<pair<Node*, int>> :: iterator nextNode;
        pq.pop();
        for(nextNode = curNode.second->links.begin(); nextNode != curNode.second->links.end(); nextNode++)
        {
            int nextNodeCost = nextNode->second;
            int nextNodeId = nextNode->first->id;
            //cerr << curNodeId << " " << curNodeCost << "\n";
            if(curNodeCost + nextNodeCost < cst[nextNodeId])
            {
                cst[nextNodeId] = curNodeCost + nextNodeCost;
                par[nextNodeId] = curNodeId;
                pq.push({-cst[nextNodeId], nextNode->first});
            }
        }
    }
}

