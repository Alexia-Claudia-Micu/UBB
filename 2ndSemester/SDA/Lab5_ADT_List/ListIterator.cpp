#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->currentElement = this->list.headOfList;
}

void ListIterator::first(){
    this->currentElement = this->list.headOfList;
}

void ListIterator::next(){
    if(this->list.elements[this->currentElement].leftChild != )
}

bool ListIterator::valid() const{
    //TODO - Implementation
	return false;
}

TElem ListIterator::getCurrent() const{
   //TODO - Implementation
	return NULL_TELEM;
}