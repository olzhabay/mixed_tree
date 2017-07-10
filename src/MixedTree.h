#pragma once

#include "Node.h"
#include "LeafNode.h"

class MixedTree {
private:
    Node* root;
    void split(LeafNode *node);
    void merge(Node *left, Node *right);
    LeafNode* searchLeafNode(int key);
public:
    MixedTree();
    ~MixedTree();
    void insert(int key, void *value);
    void remove(int key);
    void *search(int key);
};
