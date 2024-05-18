#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

// best case = O(1)
// worst case = O(range)
// total = O(range)
BagIterator::BagIterator(const Bag& c): bag(c)
{
    this->current_element = 0;
    this->current_count_of_element = 1;
    while (this->bag.elements[this->current_element] == 0 && this->current_element <= this->bag.rangeElements)
        this->current_element ++;
}

// best case = O(1)
// worst case = O(range)
// total = O(range)
void BagIterator::first() {
    this->current_element = 0;
    this->current_count_of_element = 1;
    while (this->bag.elements[this->current_element] == 0 && this->current_element <= this->bag.rangeElements)
        this->current_element ++;

}

// best case = O(1)
// worst case = O(range)
// total = O(range)
void BagIterator::next() {
	if(this->current_element >= this->bag.rangeElements)
    {
        throw exception();
    } else {
        this->current_count_of_element++;
        if(this->current_count_of_element > this->bag.elements[this->current_element])
        {
            this->current_count_of_element = 1;
            this->current_element ++;
            while (this->bag.elements[this->current_element] == 0 && this->current_element <= this->bag.rangeElements)
                this->current_element ++;
        }
    }
}

// Theta(1)
bool BagIterator::valid() const {
	if(this->current_element < this->bag.rangeElements)
        return true;
	return false;
}

// Theta(1)
TElem BagIterator::getCurrent() const
{
	if(this->current_element >= this->bag.rangeElements || this->bag.rangeElements == 0 )
    {
        throw exception();
    } else
        return this->bag.minElement + this->current_element;
}
