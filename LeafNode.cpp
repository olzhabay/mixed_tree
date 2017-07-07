#include <algorithm>
#include "LeafNode.h"

// Constructor
LeafNode::LeafNode() : Node(0, true) {
    this->size = 0;
    prev = nullptr;
    next = nullptr;
}

// Destructor
LeafNode::~LeafNode() {
}

// Returns node's number of keys
int LeafNode::getSize() {
    return size;
}

// Returns node's key
int LeafNode::getLeafKey(int index) {
    return storage[index].key;
}

// Returns node's pointer
void *LeafNode::getPtr(int index) {
    return storage[index].ptr;
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
    while (index < FANOUT && (value != storage[index].ptr || !storage[index].valid)) index++;
    return index == FANOUT ? -1 : index;
}

// get index with given key
int LeafNode::getIndex(int key) {
    int index = 0;
    while (index < FANOUT && (key != storage[index].key || !storage[index].valid)) index++;
    return index == FANOUT ? -1 : index;

    /*
    int index = 0;
    while (key != leafKey[index] && index < size)
        index++;
    return index;
     */
}


// Checks whether node is full or not
bool LeafNode::isFull() {
    return FANOUT == size;
}

void LeafNode::setNextLeaf(LeafNode *ptr) {
    next = ptr;
}

void LeafNode::setPrevleaf(LeafNode *ptr) {
    prev = ptr;
}

// Deletes key and pointer from leaf node (key)
// TODO: atomicity
// Mark spot not valid
void LeafNode::remove(int index) {
    storage[index].valid = false;
    size--;

    /*
	if (index >= size) return;
	for (int i = index; i < size-1; i++) {
		leafKey[i] = leafKey[i+1];
		ptr[i] = ptr[i+1];
	}
	size--;
	leafKey[size] = 0;
	ptr[size] = NULL;
     */
}

// Inserts data with pointer v and key k into the leaf node
// TODO: requires atomicity
// Insert into empty spot
void LeafNode::insert(int key, void *value) {

    int index = 0;
    while (storage[index].valid) index++;
    storage[index].key = key;
    storage[index].ptr = value;
    storage[index].valid = true;
    size++;

    if (getKey() > key) {
        setKey(key);
    }

    /*
	int i = size-1;
	while (i >= 0 && key < this->leafKey[i]) {
		this->ptr[i+1] = this->ptr[i];
		this->leafKey[i+1] = this->leafKey[i];
		i--;
	}
	this->leafKey[i+1] = key;
	this->ptr[i+1] = value;
	size++;
    if (Node::getKey() != leafKey[0]) {
        Node::setKey(leafKey[0]);
    }
    */
}

void LeafNode::split(LeafNode *a, LeafNode *b) {
    sort();
    for (int i = size/2; i >= 0; i--) {
        a->insert(storage[i].key, storage[i].ptr);
    }
    for (int i = size-1; i > size/2; i--) {
        b->insert(storage[i].key, storage[i].ptr);
    }

}

void LeafNode::sort() {
    std::sort(storage, storage+size, [](const kvStore &v1, const kvStore &v2) -> bool {
        return v1.key > v2.key;
    });
}
