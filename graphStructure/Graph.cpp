#include "Graph.h"

Graph::Graph(bool isDirected, bool isWeighted)
{
    this->isDirected = isDirected;
    this->isWeighted = isWeighted;

    nodeCount = 0;
    nodeLabels = {};
    edges = {};
    nodes = {};
}

void Graph::addEdge(Edge edge)
{
    edges.emplace_back(edge);

    edge.from->links.insert(make_pair(edge.to, edge.weight));
    if(!Graph::isDirected)
        edge.to->links.insert(make_pair(edge.from, edge.weight));
}

void Graph::addNode(Node *node)
{

    node->id = nodeCount++;
    ids[node->label] = node->id;

    nodeLabels.push_back(node->label);
    nodes.insert(node);
}

