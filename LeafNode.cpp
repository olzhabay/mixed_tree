/**
 *
 *      TreeNode Class
 *
 */

#include <malloc.h>
#include "LeafNode.h"

// Constructor
LeafNode::LeafNode() : Node(0, true) {
    this->numKeys = 0;
    for (int i = 0; i < FANOUT-1; i++) {
        leafKey[i] = 0;
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
int LeafNode::getLeafKey(int index) {
    return leafKey[index];
}

// Returns node's pointer
void *LeafNode::getPtr(int index) {
    return ptr[index];
}

LeafNode *LeafNode::getNextLeaf() {
    return next;
}

LeafNode *LeafNode::getPrevLeaf() {
    return prev;
}

//
int LeafNode::getIndex(void *value) {
    int index = 0;
    while (value != ptr[index] && index < numKeys)
        index++;
    return index;
}

int LeafNode::getIndex(int key) {
    int index = 0;
    while (key != leafKey[index] && index < numKeys)
        index++;
    return index;
}


// Checks whether node is full or not
bool LeafNode::isFull() {
    return FANOUT-1 == numKeys;
}

void LeafNode::setPtr(int index, void *value) {
    this->ptr[index] = value;
}

//
void LeafNode::setKey(int index, int key) {
    this->leafKey[index] = key;
}

void LeafNode::setNextLeaf(LeafNode *ptr) {
    next = ptr;
}

void LeafNode::setPrevleaf(LeafNode *ptr) {
    prev = ptr;
}

// Deletes key and pointer from leaf node (key)
// TODO: atomicity
void LeafNode::remove(int index) {
	if (index >= numKeys) return;
	for (int i = index; i < numKeys-1; i++) {
		leafKey[i] = leafKey[i+1];
		ptr[i] = ptr[i+1];
	}
	numKeys--;
	leafKey[numKeys] = 0;
	ptr[numKeys] = NULL;
}

// Inserts data with pointer v and key k into the leaf node
// TODO: requires atomicity
void LeafNode::insert(int key, void *value) {
	int i = numKeys-1;
	while (i >= 0 && key < this->leafKey[i]) {
		this->ptr[i+1] = this->ptr[i];
		this->leafKey[i+1] = this->leafKey[i];
		i--;
	}
	this->leafKey[i+1] = key;
	this->ptr[i+1] = value;
	numKeys++;
    if (Node::getKey() != leafKey[0]) {
        Node::setKey(leafKey[0]);
    }
}
