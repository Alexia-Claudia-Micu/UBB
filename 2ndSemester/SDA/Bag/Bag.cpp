#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#define MIN -11111;
#define MAX 111111;
using namespace std;


Bag::Bag() {
    this->elements = new TElem[0];
    this->maxElement = MIN;
    this->minElement = MAX;
    this->rangeElements = 0;
}

// Theta(1)
int Bag::normalizeIndex(int index) const{
    int normalizedIndex;
    if(this->minElement != 111111)
        normalizedIndex = index + (0 - this->minElement);
    else
        normalizedIndex = 0;
    return normalizedIndex;
}

// O(range) + Theta(1) => O(range)
// Best case = O(1)
// Worst case = worst case add = O(range)
// Total => O(range)
void Bag::add(TElem newValue) {
    if (newValue > this->maxElement || newValue < this->minElement)
        this->sizeUp(newValue);
    this->elements[this->normalizeIndex(newValue)] ++;
}

// Theta(1)
bool Bag::remove(TElem value) {
    if(value < this->minElement || value > this->maxElement)
        return false;
    if(this->elements[this->normalizeIndex(value)] == 0)
        return false;
    this->elements[this->normalizeIndex(value)] --;
	return true;
}

// Total: O(range)
void Bag::sizeUp(TElem elem){
    // case 0: first element -> Theta(1) - best case
    // case 1: elem > maxElem -> Theta(n+m), where n+m = range => Theta(range) - average case
    // case 2: elem < minElem -> Theta(n+m), where n+m = range => Theta(range)
    TElem *new_elements;
    int diff;
    if(this->rangeElements == 0)
    {
        new_elements = new TElem[1];
        this->rangeElements = 1;
        this->minElement = elem;
        this->maxElement = elem;
        new_elements[0] = 0;
        this->elements = new_elements;
        return;
    }
    if(elem < this->minElement)
    {
        diff = this->minElement - elem;
        new_elements = new TElem[this->rangeElements + diff];
        for(int i = 0; i < diff; i++)
            new_elements[i] = 0;
        for(int i = diff; i < diff + this->rangeElements; i++)
            new_elements[i] = this->elements[i - diff];
        this->minElement = elem;
    } else
    {
        diff = elem - this->maxElement;
        new_elements = new TElem[this->rangeElements + diff];
        for(int i = this->rangeElements - 1; i < this->rangeElements + diff; i++)\
            new_elements[i] = 0;
        for(int i = 0; i < rangeElements; i++)
            new_elements[i] = this->elements[i];
        this->maxElement = elem;
    }
    delete this->elements;
    this->rangeElements += diff;
    this->elements = new_elements;
}

// Theta(1)
bool Bag::search(TElem value) const {
    if(value < this->minElement || value > this->maxElement)
        return false;
    if(this->elements[normalizeIndex(value)] == 0)
        return false;
	return true;
}

// Theta(1)
int Bag::nrOccurrences(TElem elem) const {
    if (search(elem))
        return this->elements[normalizeIndex(elem)];
    return 0;
}

// Theta(range)
int Bag::size() const {
    int sum = 0;
    for(int i = 0; i < this->rangeElements; i++)
        sum += this->elements[i];
    return sum;
}

// O(range)
bool Bag::isEmpty() const {
    if (this->size())
        return false;
    return true;
}

// Theta(1) + complexity of bag iterator(average O(range) = O(range)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

// Theta(1) + complexity of delete
Bag::~Bag() {
    delete[] this->elements;
}

void Bag::intersection(const Bag &b) {
    for(int i = 0; i < this->rangeElements; i++)
        if(this->search(i + this->minElement) == true) {
            if (b.search(i + this->minElement) == false)
                while (this->search(i + this->minElement) == true)
                    this->remove(i + this->minElement);
            else
                while (this->nrOccurrences(i + this->minElement) > min(this->nrOccurrences(i + this->minElement), b.nrOccurrences(i + minElement)))
                    this->remove(i + this->minElement);
        }
}
