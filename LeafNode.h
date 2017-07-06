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
    int32_t numKeys ; // number of keys in this node
    int32_t leafKey[FANOUT]; // the values in this node
    void *ptr[FANOUT]; // pointers to data
    LeafNode *prev;
    LeafNode *next;

public:
    LeafNode();
    ~LeafNode();
    int getNumKeys();
    int getLeafKey(int index);
    void *getPtr(int index);
    LeafNode *getNextLeaf();
    LeafNode *getPrevLeaf();
    int getIndex(void* value);
    int getIndex(int key);
    void setNextLeaf(LeafNode *ptr);
    void setPrevleaf(LeafNode *ptr);
    void setPtr(int index, void *value);
    void setKey(int index, int key);
    void remove(int index);
    void insert(int key, void *value);
    bool isFull();
};
