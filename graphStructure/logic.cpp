#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <bits/stdc++.h>
using namespace std;

int weight;
string from, to;
bool isDirected, isWeighted;

int main()
{
    cin >> isDirected >> isWeighted;

    Graph g = Graph(isDirected, isWeighted);

    if(!isWeighted) {
        while(cin >> from){
            cin >> to;
            if(from == "-1")
                break;
            Node *u = new Node(from), *v = new Node(to);
            g.addNode(*u);
            g.addNode(*v);
            Edge e = Edge(u, v);
            g.addEdge(e);
            cout << "here" << endl;
        }
    }
    else {
        while(cin >> from >> to >> weight){

        }
    }

    cout << "out" << endl;

    for(auto i: g.edges) {
        cout << i.from->label << " " << i.to->label << endl;
    }
}