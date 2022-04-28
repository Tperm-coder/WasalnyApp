#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Bfs.cpp"
#include "Bellman.cpp"
#include "Dijkstra.cpp"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nodes, edges;
    bool isDirected, isWeighted;

    cin >> isDirected >> isWeighted >> nodes >> edges;

    Graph g = Graph(isDirected, isWeighted);

    for (int i = 0; i < edges; i++) {
        int weight = 1;
        string from, to;

        cin >> from >> to;
        if (isWeighted)
            cin >> weight;

        Node *u = new Node(from), *v = new Node(to);

        u = g.addNode(u);
        v = g.addNode(v);
        Edge e = Edge(u, v, weight);
        g.addEdge(e);
    }
}