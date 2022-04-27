#include "Node.h"

Node::Node(string label){
    this->label = label;
}

bool Node::operator == (const Node *n) {
    return label == n->label;
}