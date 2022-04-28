#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Dijkstra.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nodes, edges;
    bool isDirected, isWeighted;

    cin >> isDirected >> isWeighted >> nodes >> edges;

    Graph g = Graph(isDirected, isWeighted);

    for (int i = 0; i < edges; i++) {
        int weight;
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

    cerr << g.nodes.size() << "\n";
    for(auto i : g.nodes[0]->links)
    {
        cout << i.first->label << " " << i.second << "\n";
    }
    Dijkstra d = Dijkstra(g.nodes[0],g.nodes[2]);
    cout << d.cst[2] << "\n";
}