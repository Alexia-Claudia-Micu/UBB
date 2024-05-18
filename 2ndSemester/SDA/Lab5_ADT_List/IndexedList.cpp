#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"
#define LIST_CAPACITY 2

IndexedList::IndexedList() {
    this->elements = new Node[LIST_CAPACITY];
    this->capacity = LIST_CAPACITY;
    this->numberOfElements = NULL_TELEM;
    this->headOfList = this->capOfList = NULL_TELEM;
}

int IndexedList::size() const {
    return this->numberOfElements;
}


bool IndexedList::isEmpty() const {
    return this->numberOfElements == 0;
}

TElem IndexedList::getElement(int pos) const {
    int initialPosition = this->headOfList;
    int element = NULL_TELEM;
    

    return NULL_TELEM;
}

TElem IndexedList::setElement(int pos, TElem e) {
    TElem previousElement = this->elements[pos].info;
    this->elements[pos].info = e;
	return previousElement;
}

void IndexedList::addToEnd(TElem e) {
    if(this->elements[capOfList].info > e)
        this->elements[capOfList].leftChild = e;


}

void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
}

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
	return NULL_TELEM;
}

int IndexedList::search(TElem e) const{
    //TODO - Implementation
	return 0;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//TODO - Implementation
}