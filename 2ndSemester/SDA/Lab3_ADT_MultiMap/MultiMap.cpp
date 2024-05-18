#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
    this->dllaList = this->initializeFreeSpaceKeys(2);
}

DLLAKeys MultiMap::initializeFreeSpaceValues(int capacity, int keyIndex) {
    DLLAKeys key;
    key.valuesOfKey = new DLLAValues[capacity];
    key.capacityOfKey = capacity;
    key.tailOfKey = 0;
    key.firstFreeOfKey = 0;
    key.headOfKey = 0;
    for(int i = 0; i < capacity; i++){
        key.keyInfo = keyIndex;
        key.valuesOfKey[i].pairInfo.first = keyIndex;
        key.valuesOfKey[i].previousValue = i - 1;
        key.valuesOfKey[i].nextValue = i + 1;
    }
    //key.valuesOfKey[capacity - 1].nextValue = -1;
    return key;
}

DLLAList MultiMap::initializeFreeSpaceKeys(int capacity) {
    DLLAList list;
    list.keys = new DLLAKeys[capacity];
    list.capacityOfList = capacity;
    list.tailOfList = 0;
    list.headOfList = 0;
    list.firstFreeOfList = 0;
    for(int i = 0; i < list.capacityOfList; i++){
        list.keys[i] = this->initializeFreeSpaceValues(2, NULL_TVALUE);
        list.keys[i].nextKey = i + 1;
        list.keys[i].previousKey = i - 1;
    }
    //list.keys[capacity - 1].nextKey = -1;
    return list;
}

void MultiMap::resizeKeys() {
    DLLAList newKeys;
    newKeys = this->initializeFreeSpaceKeys(this->dllaList.capacityOfList * 2);
    for(int i = this->dllaList.headOfList; true; i = this->dllaList.keys[i].nextKey) {
        newKeys.keys[i] = this->dllaList.keys[i];
        if(i == this->dllaList.tailOfList) {
            newKeys.keys[i].nextKey = this->dllaList.capacityOfList;
            newKeys.keys[this->dllaList.capacityOfList].previousKey = i;

            break;
        }
    }
    newKeys.firstFreeOfList = this->dllaList.firstFreeOfList;
    newKeys.tailOfList = this->dllaList.tailOfList;
    newKeys.headOfList = this->dllaList.headOfList;
    delete this->dllaList.keys;
    this->dllaList = newKeys;

}

void MultiMap::resizeValues(int keyIndex, TKey key) {
    DLLAKeys newValues;
    newValues = this->initializeFreeSpaceValues(this->dllaList.keys[keyIndex].capacityOfKey * 2, key);
    for(int i = this->dllaList.keys[keyIndex].headOfKey; true; i = this->dllaList.keys[keyIndex].valuesOfKey[i].nextValue) {
        newValues.valuesOfKey[i] = this->dllaList.keys[keyIndex].valuesOfKey[i];
        if(i == this->dllaList.keys[keyIndex].tailOfKey)
            break;
    }
    newValues.firstFreeOfKey = this->dllaList.keys[keyIndex].capacityOfKey;
    newValues.tailOfKey = this->dllaList.keys[keyIndex].tailOfKey;
    newValues.nextKey = this->dllaList.keys[keyIndex].nextKey;
    newValues.headOfKey = this->dllaList.keys[keyIndex].headOfKey;
    newValues.previousKey = this->dllaList.keys[keyIndex].previousKey;
    newValues.keyInfo = key;
    delete this->dllaList.keys[key].valuesOfKey;
    this->dllaList.keys[keyIndex] = newValues;
}


void MultiMap::addValueToKey(int i, int c, int v) {
    this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].firstFreeOfKey].previousValue = this->dllaList.keys[i].tailOfKey;
    this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].firstFreeOfKey].pairInfo.first = c;
    this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].firstFreeOfKey].pairInfo.second = v;
    //this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].tailOfKey].nextValue = this->dllaList.keys[i].firstFreeOfKey;
    this->dllaList.keys[i].tailOfKey = this->dllaList.keys[i].firstFreeOfKey;
    this->dllaList.keys[i].firstFreeOfKey = this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].firstFreeOfKey].nextValue;
}

void MultiMap::add(TKey c, TValue v) {
    int i;
    for(i = this->dllaList.headOfList; i != this->dllaList.tailOfList && this->dllaList.keys[i].keyInfo != c; i = this->dllaList.keys[i].nextKey);
    if(this->dllaList.keys[i].keyInfo == c){ // add a value to existing key
        if(this->dllaList.keys[i].firstFreeOfKey == this->dllaList.keys[i].capacityOfKey){
            this->resizeValues(i, c);
        }
        this->addValueToKey(i, c, v);
    }
    else{ // add new key and value
        if(this->dllaList.firstFreeOfList == this->dllaList.capacityOfList){
            this->resizeKeys();
        }
        //this->dllaList.keys[this->dllaList.firstFreeOfList] = this->initializeFreeSpaceValues(2, c);
        this->dllaList.keys[this->dllaList.firstFreeOfList].keyInfo = c;
        this->dllaList.keys[this->dllaList.firstFreeOfList].previousKey = this->dllaList.tailOfList;
        this->addValueToKey(this->dllaList.firstFreeOfList, c, v);
        this->dllaList.tailOfList = this->dllaList.firstFreeOfList;
        this->dllaList.firstFreeOfList = this->dllaList.keys[this->dllaList.firstFreeOfList].nextKey;
    }
}


bool MultiMap::remove(TKey c, TValue v) {
    int i, j;
    for(i = this->dllaList.headOfList; i != this->dllaList.tailOfList && this->dllaList.keys[i].keyInfo != c; i = this->dllaList.keys[i].nextKey);
    if(i == this->dllaList.tailOfList && this->dllaList.keys[i].keyInfo != c)
        return false;
    if(this->dllaList.keys[i].headOfKey == this->dllaList.keys[i].tailOfKey){
        if(this->dllaList.tailOfList == this->dllaList.headOfList){//TODO  whatere values with no text is
            if(this->dllaList.keys[this->dllaList.tailOfList].valuesOfKey->pairInfo.second == v) {
                this->dllaList = this->initializeFreeSpaceKeys(2);
                return true;
            }
            return false;
        }
        if(this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].headOfKey].pairInfo.second != v)
            return false;
        if(this->dllaList.headOfList == i)
            this->dllaList.headOfList = this->dllaList.keys[i].nextKey;
        if(this->dllaList.tailOfList == i)
            this->dllaList.tailOfList = this->dllaList.keys[i].previousKey;
        this->dllaList.keys[this->dllaList.keys[i].previousKey].nextKey = this->dllaList.keys[i].nextKey;
        this->dllaList.keys[this->dllaList.keys[i].nextKey].previousKey = this->dllaList.keys[i].previousKey;

        this->dllaList.keys[i].nextKey = this->dllaList.firstFreeOfList;
        this->dllaList.firstFreeOfList = i;
    }// Remove key
    else{
        for(j = this->dllaList.keys[i].headOfKey; j != this->dllaList.keys[i].tailOfKey && this->dllaList.keys[i].valuesOfKey[j].pairInfo.second != v; j = this->dllaList.keys[i].valuesOfKey[j].nextValue);
        if(j == this->dllaList.keys[i].tailOfKey && this->dllaList.keys[i].valuesOfKey[j].pairInfo.second != v)
            return false;
        if(this->dllaList.keys[i].tailOfKey == j)
            this->dllaList.keys[i].tailOfKey = this->dllaList.keys[i].valuesOfKey[j].previousValue;
        if(this->dllaList.keys[i].headOfKey == j)
            this->dllaList.keys[i].headOfKey = this->dllaList.keys[i].valuesOfKey[j].nextValue;

        this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].valuesOfKey[j].previousValue].nextValue = this->dllaList.keys[i].valuesOfKey[j].nextValue;
        this->dllaList.keys[i].valuesOfKey[this->dllaList.keys[i].valuesOfKey[j].nextValue].previousValue = this->dllaList.keys[i].valuesOfKey[j].previousValue;

        this->dllaList.keys[i].valuesOfKey[j].nextValue = this->dllaList.keys[i].firstFreeOfKey;
        this->dllaList.keys[i].firstFreeOfKey = j;

    } // remove value
	return true;
}


vector<TValue> MultiMap::search(TKey c) const {
    int i;
    vector<TValue> valuesOfKey;
    if(this->isEmpty())
        return valuesOfKey;
    for(i = this->dllaList.headOfList; i != this->dllaList.tailOfList && this->dllaList.keys[i].keyInfo != c; i = this->dllaList.keys[i].nextKey);
    if(this->dllaList.keys[i].keyInfo == c){
        for(int j = this->dllaList.keys[i].headOfKey; true; j = this->dllaList.keys[i].valuesOfKey[j].nextValue) {
            valuesOfKey.push_back(this->dllaList.keys[i].valuesOfKey[j].pairInfo.second);
            if(j == this->dllaList.keys[i].tailOfKey)
                break;
        }
    }
	return valuesOfKey;
}


int MultiMap::size() const {
    int size = 0, i = -1;
    do{
        if(i == -1) {
            i = this->dllaList.headOfList;
            if(this->dllaList.firstFreeOfList == i)
                break;
        }
        else
            i = this->dllaList.keys[i].nextKey;
        int j = -1;
        do{
            if(j == -1)
                j = this->dllaList.keys[i].headOfKey;
            else
                j = this->dllaList.keys[i].valuesOfKey[j].nextValue;
            size ++;
        } while (j != this->dllaList.keys[i].tailOfKey);

    } while (i != this->dllaList.tailOfList);
    return size;
}


bool MultiMap::isEmpty() const {
    return this->size() == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	if(this->isEmpty())
        return;
//    for(int i = this->dllaList.headOfList; i != this->dllaList.tailOfList; i++)
//        delete this->dllaList.keys[i].valuesOfKey;
//    delete this->dllaList.keys;
}

