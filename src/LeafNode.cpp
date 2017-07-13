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
int LeafNode::getTotalSize() {
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
    while (index < FANOUT && (value != storage[index].ptr || !storage[index].valid))
        index++;
    return index == FANOUT ? -1 : index;
}

// get index with given key
int LeafNode::getIndex(int key) {
    int index = 0;
    while (index < FANOUT && (key != storage[index].key || !storage[index].valid))
        index++;
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
    vsize--;

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

    storage[size].key = key;
    storage[size].ptr = value;
    storage[size].valid = true;
    size++;
    vsize++;

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
    for (int i = vsize/2; i >= 0; i--) {
        a->insert(storage[i].key, storage[i].ptr);
    }
    for (int i = vsize-1; i > vsize/2; i--) {
        b->insert(storage[i].key, storage[i].ptr);
    }

}

void LeafNode::sort() {
    std::sort(storage, storage+size, [](const kvStore &v1, const kvStore &v2) -> bool {
        return v1.valid && v2.valid && v1.key > v2.key;
    });
}

int LeafNode::getValidSize() {
    return vsize;
}

bool LeafNode::getValid(int index) {
    return storage[index].valid;
}
