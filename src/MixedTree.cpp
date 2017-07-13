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
    if (l->getValidSize() + r->getValidSize() > FANOUT) return;
    // creating new node and copying valid values into it
    LeafNode *node = new LeafNode();
    for (int i = 0; i < l->getTotalSize(); i++)
        if (l->getValid(i))
            node->insert(l->getLeafKey(i), l->getPtr(i));
    for (int i = 0; i < r->getTotalSize(); i++)
        if (r->getValid(i))
            node->insert(r->getLeafKey(i), r->getPtr(i));
    // assigning parent-child pointers
    Node *parent = l->getParent()->getParent();
    node->setParent(parent);
    if (parent->getKey()<node->getKey())
        parent->setRight(node);
    else
        parent->setLeft(node);
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
    if (node->getParent()->getLeft()->isLeaf() &&
            node->getParent()->getRight()->isLeaf()) {
        merge(node->getParent()->getLeft(), node->getParent()->getRight());
    }
}

void *MixedTree::search(int key) {
    LeafNode *node = searchLeafNode(key);
    return node->getPtr(node->getIndex(key));
}

