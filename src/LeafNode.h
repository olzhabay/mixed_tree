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
    struct kvStore {
        int32_t key;
        void *ptr;
        bool valid;
    };

private:
    kvStore storage[FANOUT];
    //int32_t leafKey[FANOUT]; // the values in this node
    //void *ptr[FANOUT]; // pointers to data
    LeafNode *prev;
    LeafNode *next;
    uint16_t size; // number of all keys in this node
    uint16_t vsize; // number of valid keys

public:
    LeafNode();
    ~LeafNode();
    int getTotalSize();
    int getValidSize();
    int getLeafKey(int index);
    void *getPtr(int index);
    bool getValid(int index);
    LeafNode *getNextLeaf();
    LeafNode *getPrevLeaf();
    int getIndex(void* value);
    int getIndex(int key);
    void setNextLeaf(LeafNode *ptr);
    void setPrevleaf(LeafNode *ptr);
    void remove(int index);
    void insert(int key, void *value);
    bool isFull();
    void split(LeafNode *a, LeafNode *b);
    void sort();
};
