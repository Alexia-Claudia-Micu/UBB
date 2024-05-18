#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    this->currentKey = this->col.dllaList.headOfList;
    this->currentValueOfKey = this->col.dllaList.keys[this->currentKey].headOfKey;
    this->isValid = 1;
}

TElem MultiMapIterator::getCurrent() const{
    if(!this->valid())
        throw exception();
	TElem current;
    current.first = this->col.dllaList.keys[this->currentKey].keyInfo;
    current.second = this->col.dllaList.keys[this->currentKey].valuesOfKey[this->currentValueOfKey].pairInfo.second;
	return current;
}

bool MultiMapIterator::valid() const {
    if(this->col.isEmpty())
        return false;
    return this->isValid == 1;
}

void MultiMapIterator::next() {
    if(!this->valid())
        throw exception();
	if(this->currentValueOfKey != this->col.dllaList.keys[this->currentKey].tailOfKey){
        this->currentValueOfKey = this->col.dllaList.keys[this->currentKey].valuesOfKey[this->currentValueOfKey].nextValue;
        return;
    } else{
        if(this->currentKey == this->col.dllaList.tailOfList) {
            this->isValid = 0;
            return;
        }
        this->currentKey = this->col.dllaList.keys[this->currentKey].nextKey;
        this->currentValueOfKey = this->col.dllaList.keys[this->currentKey].headOfKey;
    }
}

void MultiMapIterator::first() {
    this->currentKey = this->col.dllaList.headOfList;
    this->currentValueOfKey = this->col.dllaList.keys[this->currentKey].headOfKey;
    this->isValid = 1;
}

