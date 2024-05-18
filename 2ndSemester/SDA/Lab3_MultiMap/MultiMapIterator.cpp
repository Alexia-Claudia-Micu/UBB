#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    this->currentKey = this->col.headOfKeys;
    this->currentValueOfKey = this->col.dlla[this->col.headOfKeys].headOfValues;
}

TElem MultiMapIterator::getCurrent() const{
	TElem current;
    if(!this->valid())
        throw exception();
    current.first = this->col.dlla[this->currentKey].keyInfo;
    current.second = this->col.dlla[this->currentKey].values[this->currentValueOfKey].info;
    return current;
}

bool MultiMapIterator::valid() const {
	if(this->currentKey == this->col.tailOfKeys)
        return false;
	return true;
}

void MultiMapIterator::next() {
    if(!this->valid())
        throw exception();
    this->currentValueOfKey = this->col.dlla[this->currentKey].values[this->currentValueOfKey].nextValue;
    if(this->currentValueOfKey == this->col.dlla[this->currentKey].tailOfValues){
        this->currentKey = this->col.dlla[this->currentKey].nextKey;
        while (this->valid()) {
            this->currentValueOfKey = this->col.dlla[this->currentKey].headOfValues;
            if(this->currentValueOfKey == this->col.dlla[this->currentKey].tailOfValues)
                this->currentKey = this->col.dlla[this->currentKey].nextKey;
            else
                break;
        }
    }
}

void MultiMapIterator::first() {
    this->currentKey = this->col.headOfKeys;
    this->currentValueOfKey = this->col.dlla[this->col.headOfKeys].headOfValues;
}

