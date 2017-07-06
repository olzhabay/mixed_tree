//
// Created by olzhas on 7/4/17.
//

#include "Node.h"

Node::Node() {
}

Node::Node(int key, bool leaf) {
    this->key = key;
    this->leaf = leaf;
    left = nullptr;
    right = nullptr;
}


Node::Node(int key, Node *left, Node *right) {
    this->key = key;
    leaf = false;
    this->left = left;
    this->right = right;
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

Node *Node::getLeft() {
    return left;
}

Node *Node::getRight() {
    return right;
}

int32_t Node::getKey() {
    return key;
}

void Node::setKey(int32_t key) {
    this->key = key;
}

Node *Node::getParent() {
    return parent;
}

void Node::setParent(Node *ptr) {
    parent = ptr;
}
