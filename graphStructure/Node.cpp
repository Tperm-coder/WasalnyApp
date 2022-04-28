#include "Node.h"

Node::Node(string label)
{
    this->label = label;
}

bool Node::operator == (const Node *node)
{
    return label == node->label;
}