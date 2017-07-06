#include "MixedTree.h"

MixedTree::MixedTree() {
    root = new LeafNode();
}

MixedTree::~MixedTree() {

}

void MixedTree::split(LeafNode *node) {
    Node *grandparent = node->getParent();
    LeafNode *a = new LeafNode();
    for (int i = node->getNumKeys()/2; i >= 0; i--) {
        a->insert(node->getLeafKey(i), node->getPtr(i));
    }
    LeafNode *b = new LeafNode();
    for (int i = node->getNumKeys()-1; i > node->getNumKeys()/2; i--) {
        b->insert(node->getLeafKey(i), node->getPtr(i));
    }
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

void MixedTree::merge(Node *node, Node *left, Node *right) {

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

}

void *MixedTree::search(int key) {
    LeafNode *node = searchLeafNode(key);
    return node->getPtr(node->getIndex(key));
}

