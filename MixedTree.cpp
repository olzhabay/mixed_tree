#include "MixedTree.h"

MixedTree::MixedTree() {
    root = new LeafNode();
}

MixedTree::~MixedTree() {

}

void MixedTree::split(LeafNode *node) {
    Node *grandparent = node->getParent();
    LeafNode *a = new LeafNode();
    LeafNode *b = new LeafNode();
    node->split(a, b);
    Node *parent = new Node(b->getKey(), a, b);
    parent->setParent(grandparent);
    a->setParent(parent);
    b->setParent(parent);
    if (grandparent != nullptr) {
        if (grandparent->getLeft() == node)
            grandparent->setLeft(parent);
        else
            grandparent->setRight(parent);
    }

}

void MixedTree::merge(Node *left, Node *right) {
    LeafNode *l = static_cast<LeafNode*>(left);
    LeafNode *r = static_cast<LeafNode*>(right);
    // check if merge is possible
    if (l->getSize() + r->getSize() > FANOUT/2 + FANOUT%2) return;
    LeafNode *node = new LeafNode();
    
}

LeafNode *MixedTree::searchLeafNode(int key) {
    Node *node = root;
    while (!node->isLeaf()) {
        node = node->getKey() <= key ? node->getRight() : node->getLeft();
    }
    return static_cast<LeafNode*>(node);
}

void MixedTree::insert(int key, void *value) {
    LeafNode *node = searchLeafNode(key);
    node->insert(key, value);
    if (node->isFull())
        split(node);
}

void MixedTree::remove(int key) {
    LeafNode *node = searchLeafNode(key);
    node->remove(node->getIndex(key));
    // TODO: merge if empty
    if (node->getParent()->getLeft()->isLeaf() &&
            node->getParent()->getRight()->isLeaf()) {
        merge(node->getParent()->getLeft(), node->getParent()->getRight());
    }
}

void *MixedTree::search(int key) {
    LeafNode *node = searchLeafNode(key);
    return node->getPtr(node->getIndex(key));
}

