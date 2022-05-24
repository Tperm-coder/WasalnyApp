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

void Graph::addEdge(Edge *edge)
{
    edges.emplace_back(*edge, edge);
    edge->from->links.insert({edge->to, edge});

    if(!this->isDirected) {
        edges.push_back({{edge->to, edge->from, edge->weight}, edge});
        edge->to->links.insert({edge->from, edge});
    }

    if (edge->weight < 0)
        countNegative++;
}

Node* Graph::addNode(Node *node)
{
    if(!ids.count(node->label))
    {
        node->id = nodeCount++;
        ids[node->label] = node->id;
        nodeLabels.push_back(node->label);
        nodes.push_back(node);
    }
    else
        node = nodes[ids[node->label]];
    return node;
}