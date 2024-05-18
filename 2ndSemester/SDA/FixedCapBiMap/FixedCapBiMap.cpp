#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

using namespace std;

//Theta(1)
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if(capacity <= 0)
        throw exception();
    this->elements = new TElem[capacity];
    this->capacity = capacity;
    this->nrPairs = 0;
}
//Theta(1)
FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
// O(nrPairs)
bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->nrPairs == this->capacity)
        throw exception();
    ValuePair values = this->search(c);
    if(values.second == NULL_TVALUE)
    {
        this->elements[this->nrPairs].first = c;
        this->elements[this->nrPairs].second = v;
        this->nrPairs++;
        return 1;
    }
    return false;
}
// O(nrPairs)
ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair  values;
    values.first = NULL_TVALUE;
    values.second = NULL_TVALUE;

    for (int i = 0; i < this->nrPairs; i++)
    {
        if(this->elements[i].first == c)
        {
            if(values.first == NULL_TVALUE)
                values.first = this->elements[i].second;
            else
                values.second = this->elements[i].second;
        }
    }
    return values;
}
//Best case: O(1)
//Worst case: O(nrPairs)
//Total complexity: O(nrPairs)
bool FixedCapBiMap::remove(TKey c, TValue v){
	for( int i = 0; i < this->nrPairs; i++)
        if(this->elements[i].first == c && this->elements[i].second == v) {
            this->elements[i] = this->elements[nrPairs - 1];
            this->nrPairs--;
            return true;
        }
    return false;
}

//Theta(1)
int FixedCapBiMap::size() const {
    return this->nrPairs;
}
//Theta(1)
bool FixedCapBiMap::isEmpty() const{
    return this->nrPairs == 0;
}
//Theta(1)
bool FixedCapBiMap::isFull() const {
    return this->nrPairs == capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



