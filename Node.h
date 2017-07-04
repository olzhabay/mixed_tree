#pragma once

#include <fsimage.h>

/*
 * Node class
 *
 */

class Node {
private:
    int32_t key;
    int32_t priority;
    Node* left;
    Node* right;
    bool leaf;
public:
    Node();
    Node(int key, int priority, bool leaf = false);
    virtual ~Node();
    virtual void insert(int key, void *value) = 0;
    virtual void remove(int key) = 0;
    virtual bool isFull() = 0;
    bool isLeaf();
    void setLeft(Node* left);
    void setRight(Node* right);
    int32_t getPriority();
    Node* getLeft();
    Node* getRight();
};
