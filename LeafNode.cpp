/**
 *
 *      TreeNode Class
 *
 */

#include <malloc.h>
#include "LeafNode.h"

// Constructor
LeafNode::LeafNode() {
    Node(0, 0, true);
    parent = NULL;
    this->numKeys = 0;
    for (int i = 0; i < FANOUT-1; i++) {
        leafkey[i] = 0;
        ptr[i] = NULL;
    }
    ptr[FANOUT-1] = NULL;
}

// Destructor
LeafNode::~LeafNode() {
}

// Returns node's number of keys
int LeafNode::getNumKeys() {
    return numKeys;
}

// Returns node's key
int LeafNode::getKey(int index) {
    return leafkey[index];
}

// Returns node's pointer
void* LeafNode::getPtr(int index) {
    return ptr[index];
}

// Returns parent node
void* LeafNode::getParent() {
    return this->parent;
}

void* LeafNode::getNextLeaf() {
    return ptr[FANOUT-1];
}

//
int LeafNode::getIndex(void* value) {
    int index = 0;
    while (value != ptr[index] && index < numKeys)
        index++;
    return index;
}

// Checks whether node is full or not
bool LeafNode::isFull() {
    return FANOUT-1 == numKeys;
}

void LeafNode::setPtr(int index, void* value) {
    this->ptr[index] = value;
}

//
void LeafNode::setKey(int index, int key) {
    this->leafkey[index] = key;
}

// Sets pointer as a parent of the node
void LeafNode::setParent(void* parent) {
    this->parent = parent;
}

void LeafNode::setNextLeaf(void *value) {
    ptr[FANOUT-1] = value;
}

// Deletes key and pointer from leaf node (index)
void LeafNode::remove(int index) {
	if (index >= numKeys) return;
	for (int i = index; i < numKeys-1; i++) {
		leafkey[i] = leafkey[i+1];
		ptr[i] = ptr[i+1];
	}
	numKeys--;
	leafkey[numKeys] = 0;
	ptr[numKeys] = NULL;
}

// Inserts data with pointer v and key k into the leaf node
void LeafNode::insert(int key, void *value) {
	int i = numKeys-1;
	while (i >= 0 && key < this->leafkey[i]) {
		this->ptr[i+1] = this->ptr[i];
		this->leafkey[i+1] = this->leafkey[i];
		i--;
	}
	this->leafkey[i+1] = key;
	this->ptr[i+1] = value;
	numKeys++;
}
