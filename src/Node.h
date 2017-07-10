#pragma once

#include <cstdint>

/*
 * Node class
 *
 */

class Node {
private:
    int32_t key;
    Node *left;
    Node *right;
    Node *parent;
    bool leaf;
public:
    Node();
    Node(int key, bool leaf = false);
    Node(int key, Node *left, Node *right);
    virtual ~Node();
    bool isLeaf();
    void setLeft(Node* left);
    void setRight(Node* right);
    void setKey(int32_t key);
    void setParent(Node *ptr);
    Node *getLeft();
    Node *getRight();
    Node *getParent();
    int32_t getKey();

};
