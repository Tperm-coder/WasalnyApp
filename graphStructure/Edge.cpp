#include "Edge.h"

Edge::Edge(Node *from, Node *to)
{
    this->from = from;
    this->to = to;
    weight = 1;
}

Edge::Edge(Node* from, Node* to, int weight)
{
    this->from = from;
    this->to = to;
    this->weight = weight;
}
