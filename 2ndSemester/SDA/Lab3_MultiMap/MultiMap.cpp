#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#define CAPACITY 10000

using namespace std;

vector<TKey> MultiMap::keySet() const {
    vector<TKey> allKeys;
    for(int i = this->headOfKeys; i != this->tailOfKeys; i = this->dlla[i].nextKey)
        allKeys.push_back(this->dlla[i].keyInfo);
    return allKeys;
}

MultiMap::MultiMap() {
    this->dlla = this->reserveSpaceForDLLA(CAPACITY);

    this->capacity = CAPACITY;
    this->tailOfKeys = 0;
    this->headOfKeys = 0;
}

// Theta(capacity) -> O(n)
DLLAKey MultiMap::reserveSpaceForKey(int capacity) {
    DLLAKey newKey;
    newKey.capacity = capacity;
    newKey.values = new Value[capacity + 1];
    newKey.keyInfo = NULL_TVALUE;
    newKey.headOfValues = 0;
    newKey.tailOfValues = 0;
    for (int i = 0; i <= capacity; ++i) {
        newKey.values[i].previousValue = i - 1;
        newKey.values[i].nextValue = i + 1;
    }
    return newKey;
}

// Theta(capacity * 2) -> O(2*n) -> O(n)
DLLAKey* MultiMap::reserveSpaceForDLLA(int capacity) {
    DLLAKey *newKeys = new DLLAKey[capacity + 1];
    for(int i = 0; i <= capacity; i++){
        newKeys[i] = reserveSpaceForKey(2);
        newKeys[i].previousKey = i - 1;
        newKeys[i].nextKey = i + 1;
    }
    return newKeys;
}

// Theta(newCapacity) + Theta(capacity) -> O(capacity + capacity*2) -> O(n)
void MultiMap::resizeDlla() {
    // Theta(newCapacity)
    DLLAKey *newList = this->reserveSpaceForDLLA(this->capacity*2);
    // Theta(capacity)
    for(int i = this->headOfKeys; i != this->tailOfKeys; i = this->dlla[i].nextKey){
        newList[i] = this->dlla[i];
    }
    delete this->dlla;
    this->dlla = newList;
    this->capacity = this->capacity * 2;
}

// Theta(newCapacity) + Theta(capacity) -> O(capacity + capacity*2) -> O(n)
void MultiMap::resizeKey(int keyIndex, TKey key) {
    // Theta(newCapacity)
    DLLAKey newKey = this->reserveSpaceForKey(this->dlla[keyIndex].capacity * 2);
    // Theta(capacity)
    for(int i = this->dlla[keyIndex].headOfValues; i != this->dlla[keyIndex].tailOfValues; i = this->dlla[keyIndex].values[i].nextValue){
        newKey.values[i] = this->dlla[keyIndex].values[i];
    }
    //delete this->dlla[keyIndex].values;
    this->dlla[keyIndex].values = newKey.values;
    this->dlla[keyIndex].capacity = this->dlla[keyIndex].capacity * 2;
}

// Best case: O(1); Worst case: O(n)
void MultiMap::add(TKey c, TValue v) {
    int i;
    // Best case: O(1); Worst case: O(nrKeys)
    for(i = this->headOfKeys; i != this->tailOfKeys && this->dlla[i].keyInfo != c; i = this->dlla[i].nextKey);
    if(i != this->tailOfKeys){ // add to existing key
        // we need to add to the end of the key values
        int positionToAdd = this->dlla[i].tailOfValues;
        // Best case: O(1); Worst case: O(n)
        if(positionToAdd == this->dlla[i].capacity)
            this->resizeKey(i, c);
        this->dlla[i].values[positionToAdd].info = v;
        this->dlla[i].tailOfValues = this->dlla[i].values[positionToAdd].nextValue;
    } else{ //add new key
        int positionToAdd = this->tailOfKeys;
        // Best case: O(1); Worst case: O(n)
        if(this->tailOfKeys == this->capacity)
            this->resizeDlla();
        this->dlla[positionToAdd].keyInfo = c;
        this->dlla[positionToAdd].values[0].info = v;
        this->dlla[positionToAdd].tailOfValues = 1;

        this->tailOfKeys = this->dlla[this->tailOfKeys].nextKey;
    }
}

// Best case: O(1); Worst case: O(nrKeys + nrValues + n) -> O(3*n) -> O(n)
bool MultiMap::remove(TKey c, TValue v) {
    int i, j;
    // Best case: O(1); Worst case: O(nrKeys)
	for(i = this->headOfKeys; i != this->tailOfKeys && this->dlla[i].keyInfo != c; i = this->dlla[i].nextKey)
        ;
    if(i == this->tailOfKeys)
        return false;
    // Best case: O(1); Worst case: O(nrValues)
    for(j = this->dlla[i].headOfValues; j != this->dlla[i].tailOfValues && this->dlla[i].values[j].info != v; j = this->dlla[i].values[j].nextValue)
        ;
    if(j == this->dlla[i].tailOfValues)
        return false;

    this->dlla[i].values[this->dlla[i].values[j].previousValue].nextValue = this->dlla[i].values[j].nextValue;
    this->dlla[i].values[this->dlla[i].values[j].nextValue].previousValue= this->dlla[i].values[j].previousValue;

    int last = this->dlla[i].values[this->dlla[i].tailOfValues].previousValue;
    this->dlla[i].values[last].nextValue = j;
    this->dlla[i].values[j].previousValue = last;

    if(this->dlla[i].values[this->dlla[i].headOfValues].nextValue == this->dlla[i].tailOfValues){
        this->dlla[this->dlla[i].previousKey].nextKey = this->dlla[i].nextKey;
        this->dlla[this->dlla[i].nextKey].previousKey = this->dlla[i].previousKey;

        int last = this->dlla[this->tailOfKeys].previousKey;
        this->dlla[last].nextKey = i;
        this->dlla[i].previousKey = last;

        // Best case O(1); Worst case: O(n)
        if(this->dlla[this->headOfKeys].nextKey == this->tailOfKeys)
        {
            // O(n)
            this->dlla = this->reserveSpaceForDLLA(CAPACITY);
            this->capacity = CAPACITY;
            this->tailOfKeys = 0;
            this->headOfKeys = 0;
            return true;
        }

        if(i == this->headOfKeys)
            this->headOfKeys = this->dlla[i].nextKey;
        this->dlla[i].nextKey = this->tailOfKeys;
        this->dlla[this->tailOfKeys].previousKey = i;
        this->tailOfKeys = i;
    }
    if(j == this->dlla[i].headOfValues)
        this->dlla[i].headOfValues = this->dlla[i].values[j].nextValue;
    this->dlla[i].values[j].nextValue = this->dlla[i].tailOfValues;
    this->dlla[i].values[this->dlla[i].tailOfValues].previousValue = j;

    this->dlla[i].tailOfValues = j;

    return true;
}

// Best case: O(1); Worst case: O(nrKeys + nrValues) -> O(2*n) -> O(n)
vector<TValue> MultiMap::search(TKey c) const {
    int i;
    // Best case: O(1); Worst case: O(nrKeys)
    for (i = this->headOfKeys; i != this->tailOfKeys && this->dlla[i].keyInfo != c; i = this->dlla[i].nextKey);
    if(i == this->tailOfKeys)
        return vector<TValue>();
    vector<TValue> result;
    // Best case: O(1); Worst case: O(nrValues)
    for(int j = this->dlla[i].headOfValues; j != this->dlla[i].tailOfValues; j = this->dlla[i].values[j].nextValue)
        result.push_back(this->dlla[i].values[j].info);
    return result;
}

// Theta (nrKeys * nrValues) -> O(n^2)
int MultiMap::size() const {
    int size = 0;
	for(int i = this->headOfKeys; i != this->tailOfKeys; i = this->dlla[i].nextKey)
        for(int j = this->dlla[i].headOfValues; j != this->dlla[i].tailOfValues; j = this->dlla[i].values[j].nextValue)
            size++;
	return size;
}

// Theta (nrKeys + nrValues) -> O(n^2)
bool MultiMap::isEmpty() const {
    return this->size() == 0;
}

// Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	delete this->dlla;
}

