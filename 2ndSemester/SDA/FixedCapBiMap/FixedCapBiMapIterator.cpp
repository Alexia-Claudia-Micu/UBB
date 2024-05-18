#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;

//Theta(1)
FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->currentPosition = 0;
}

//Theta(1)
void FixedCapBiMapIterator::first() {
    this->currentPosition = 0;
}

//O(1)
void FixedCapBiMapIterator::next() {
	if(!this->valid())
        throw exception();
    else
        this->currentPosition++;
}

// O(1)
TElem FixedCapBiMapIterator::getCurrent(){
    if(!this->valid())
        throw exception();
    else
        return this->map.elements[this->currentPosition];
}

//Theta(1)
bool FixedCapBiMapIterator::valid() const {
    return this->currentPosition < this->map.nrPairs;
}



