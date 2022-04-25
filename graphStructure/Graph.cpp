#include "Graph.h"

Graph::Graph(bool isDirected, bool isWeighted){
    this->isDirected = isDirected;
    this->isWeighted = isWeighted;
}

void Graph::addEdge(Edge edge){
    edges.emplace_back(edge);
    Node *from = edge.from, *to = edge.to;
    int weight = edge.weight;

    from->links.insert(make_pair(to, weight));
    if(!Graph::isDirected)
        to->links.insert(make_pair(from, weight));
}

void Graph::addNode(Node &node){
    node.id = nodeCount++;
    ids[node.label] = node.id;
    nodeLabels.emplace_back(node.label);
}

