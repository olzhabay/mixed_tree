#pragma once

// for debugging purpose a small page size will be helpful.
#include "Node.h"

#define PGSIZE 4096

// When you are done with debugging,
// change the PGSIZE to 4K and see if it makes performance difference.
//#define PGSIZE 4096

#define FANOUT ((PGSIZE-2*sizeof(int)-sizeof(void*))/(sizeof(int)+sizeof(void*))) + 1

class LeafNode : public Node
{
private:
    void *parent; // pointer to parent node
    int numKeys ; // number of keys in this node
    int leafkey[FANOUT-1]; // the values in this node
    void *ptr[FANOUT]; // pointers to child nodes or data if this is a leaf node

public:
    LeafNode();
    ~LeafNode();
    int getNumKeys();
    int getKey(int index);
    void* getPtr(int index);
    void* getParent();
    void* getNextLeaf();
    int getIndex(void* value);
    void setParent(void* parent);
    void setNextLeaf(void* value);
    void setPtr(int index, void* value);
    void setKey(int index, int key);
    void remove(int index);
    void insert(int key, void *value);
    bool isFull();
};
