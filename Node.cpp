//
// Created by olzhas on 7/4/17.
//

#include "Node.h"

Node::Node() {
}

Node::Node(int key, int priority, bool leaf) {
    this->key = key;
    this->priority = priority;
    this->leaf = leaf;
    left = NULL;
    right = NULL;
}

Node::~Node() {
}

bool Node::isLeaf() {
    return leaf;
}

void Node::setLeft(Node *left) {
    this->left = left;
}

void Node::setRight(Node *right) {
    this->right = right;
}

int32_t Node::getPriority() {
    return priority;
}

Node *Node::getLeft() {
    return left;
}

Node *Node::getRight() {
    return right;
}
