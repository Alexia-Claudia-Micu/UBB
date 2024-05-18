#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>
#define LIST_CAPACITY 20000


SortedIndexedList::SortedIndexedList(Relation r) {
    this->elements = new Node[LIST_CAPACITY];
    this->capacity = LIST_CAPACITY;
    this->headOfList = 0;
    this->nextFreeIndex = 0;
    this->numberOfElements = 0;
    this->relation = r;
    this->elements[0].leftChild = -1;
    this->elements[0].rightChild = -1;
    this->elements[0].elementsToTheLeft = 0;
    this->elements[0].parent = -1;
    this->elements[0].info = NULL_TCOMP;
}

// Best case: O(1)
// Average case: O(log(n))
// Worst case: O(n)
int SortedIndexedList::lastIndexOf(TComp elem) const {
    if(!this->size())
        return -1;
    int position = 0, current = this->headOfList, lastPosition =-1;
    while (current != -1){
        if(this->relation(this->elements[current].info, elem)) {
            position += this->elements[current].elementsToTheLeft+1;
            if (this->elements[current].info == elem)
                lastPosition = position-1;
            current = this->elements[current].rightChild;
        }
        else {
            current = this->elements[current].leftChild;
        }
    }
    return lastPosition;
}

int SortedIndexedList::size() const {
	return this->numberOfElements;
}

bool SortedIndexedList::isEmpty() const {
    return this->numberOfElements == 0;
}

// Best case: O(1)
// Average case: O(log(n))
// Worst case: O(n)
TComp SortedIndexedList::getElement(int i) const{
    if(i < 0 || i >= this->numberOfElements)
        throw exception();
    int currentIndex = 0, current = this->headOfList;
    while (currentIndex != i && current != -1){
        if(this->elements[current].elementsToTheLeft + currentIndex + 1 < i){
            currentIndex = this->elements[current].elementsToTheLeft + currentIndex + 1;
            current = this->elements[current].rightChild;
        } else{
            current = this->elements[current].leftChild;
        }
    }
    if(current == -1)
	    return NULL_TCOMP;
    return this->elements[current].info;
}


// Best case: O(1)
// Average case: O(log(n)) + O(log(n)) -> O(2*log(n)) -> O(log(n))
// Worst case: O(n)
TComp SortedIndexedList::remove(int i) {
    if(i == -1)
        throw exception();
    if(i < 0 || i >= this->numberOfElements) {
        throw exception();
        return NULL_TCOMP;
    }
    int currentIndex = 0, current = this->headOfList;
    // Best case: O(1)
    // Worst case: O(log(n))
    // search for the index of the element
    while (currentIndex != i && current != -1){
        if(this->elements[current].elementsToTheLeft + currentIndex < i){
            currentIndex = this->elements[current].elementsToTheLeft + currentIndex+ 1;
            current = this->elements[current].rightChild;
        } else{
            if(currentIndex + this->elements[current].elementsToTheLeft == i)
                break;
            this->elements[current].elementsToTheLeft--;
            current = this->elements[current].leftChild;
        }
    }
    int previousValue = this->elements[current].info;

    int parentIndex, leftChild, rightChild;
    parentIndex = this->elements[current].parent;
    leftChild = this->elements[current].leftChild;
    rightChild = this->elements[current].rightChild;

    if(leftChild == rightChild && rightChild == -1){  //Doesn't have children, just delete
        if(parentIndex != -1) {
            if (this->elements[parentIndex].rightChild == current)
                this->elements[parentIndex].rightChild = -1;
            else
                this->elements[parentIndex].leftChild = -1;
        }
    } else
        if(leftChild != -1 && rightChild == -1){    //Has only a left child
            if(parentIndex != -1){
                if (this->elements[parentIndex].rightChild == current)
                    this->elements[parentIndex].rightChild = leftChild;
                else
                    this->elements[parentIndex].leftChild = leftChild;
                this->elements[leftChild].parent = parentIndex;
            }
            //this->elements[leftChild].elementsToTheLeft = this->elements[current].elementsToTheLeft;
        } else
            if(leftChild == -1 && rightChild != -1){    //Has only right child
                if(parentIndex != -1){
                    if (this->elements[parentIndex].rightChild == current)
                        this->elements[parentIndex].rightChild = rightChild;
                    else
                        this->elements[parentIndex].leftChild = rightChild;
                    this->elements[rightChild].parent = parentIndex;
                }
                //this->elements[rightChild].elementsToTheLeft = this->elements[current].elementsToTheLeft;
            } else{ //Has both children
                if(this->elements[rightChild].leftChild == -1){ // rightchild becomes the node
                    if(parentIndex == -1)
                        this->headOfList = rightChild;
                    this->elements[rightChild].leftChild = leftChild;
                    this->elements[rightChild].elementsToTheLeft = this->elements[current].elementsToTheLeft;
                    this->elements[leftChild].parent = rightChild;

                    this->elements[rightChild].parent = parentIndex;
                    if(parentIndex != -1) {
                        if (this->elements[parentIndex].leftChild == current)
                            this->elements[parentIndex].leftChild = rightChild;
                        else
                            this->elements[parentIndex].rightChild = rightChild;
                    }
                } else{
                    int leftMostChildOfRightChild = rightChild;
                    // Best case: O(1)
                    // Worst case: O(log(n))
                    while (this->elements[leftMostChildOfRightChild].leftChild != -1) { // find rightmost leaf
                        this->elements[leftMostChildOfRightChild].elementsToTheLeft--;
                        leftMostChildOfRightChild = this->elements[leftMostChildOfRightChild].leftChild;
                    }
                    if(parentIndex == -1)
                        this->headOfList = leftMostChildOfRightChild;
                    int rightOrphan = this->elements[leftMostChildOfRightChild].rightChild;

                    this->elements[leftMostChildOfRightChild].leftChild = leftChild;
                    this->elements[leftMostChildOfRightChild].elementsToTheLeft = this->elements[current].elementsToTheLeft;
                    this->elements[leftChild].parent = leftMostChildOfRightChild;

                    {
                        int orphanParent = this->elements[leftMostChildOfRightChild].parent;
                        if (rightOrphan != -1) {
                            this->elements[orphanParent].leftChild = rightOrphan;
                            this->elements[rightOrphan].parent = orphanParent;
                        } else
                            this->elements[orphanParent].leftChild = -1;
                    }

                    this->elements[leftMostChildOfRightChild].parent = parentIndex;

                    if(parentIndex != -1){
                        if (this->elements[parentIndex].leftChild == current)
                            this->elements[parentIndex].leftChild = leftMostChildOfRightChild;
                        else
                            this->elements[parentIndex].rightChild = leftMostChildOfRightChild;
                    }
                    this->elements[leftMostChildOfRightChild].rightChild = rightChild;
                    this->elements[rightChild].parent = leftMostChildOfRightChild;
                }
            }

    this->numberOfElements--;
    return previousValue;
}

// Best case: O(1)
// Average case: O(log(n))
// Worst case: O(n)
int SortedIndexedList::search(TComp e) const {
    if(!this->size())
        return -1;
	int position = 0, current = this->headOfList;
    while (current != -1){
        if(this->elements[current].info == e)
            return position + this->elements[current].elementsToTheLeft;
        if(this->relation(this->elements[current].info, e)) {
            position += this->elements[current].elementsToTheLeft+1;
            current = this->elements[current].rightChild;
            if(current != -1)
                if(this->elements[current].info == e)
                    return position;
        }
        else {
            current = this->elements[current].leftChild;
        }
    }

	return -1;
}

// best case: O(1)
// average case: O(log(n) + n) -> O(n)
// worst case: O(n)
void SortedIndexedList::add(TComp e) {
    if(this->headOfList == this->nextFreeIndex){
        this->elements[headOfList].leftChild = -1;
        this->elements[headOfList].rightChild = -1;
        this->elements[headOfList].info = e;
        this->elements[headOfList].elementsToTheLeft = 0;
        this->elements[headOfList].parent = -1;
        this->numberOfElements++;
        this->nextFreeIndex++;
        return;
    }
    int current = this->headOfList;
    this->numberOfElements++;
    while (current != -1){ // best case: O(1) Worst case: O(log2(nrElements) + n)-> O(log(n) + n)
        if(this->relation(this->elements[current].info, e)) {
            if(this->capacity == this->numberOfElements)
                this->resize(); // O(n)
            if(this->elements[current].rightChild == -1){
                this->elements[current].rightChild = this->nextFreeIndex;
                this->elements[nextFreeIndex].rightChild = -1;
                this->elements[nextFreeIndex].leftChild = -1;
                this->elements[nextFreeIndex].info = e;
                this->elements[nextFreeIndex].elementsToTheLeft = 0;
                this->elements[nextFreeIndex].parent = current;
                this->nextFreeIndex++;
                return;
            }
            current = this->elements[current].rightChild;
        }
        else {
            if(this->elements[current].leftChild == -1){
                this->elements[current].leftChild = this->nextFreeIndex;
                this->elements[nextFreeIndex].rightChild = -1;
                this->elements[nextFreeIndex].leftChild = -1;
                this->elements[nextFreeIndex].info = e;
                this->elements[nextFreeIndex].elementsToTheLeft = 0;
                this->elements[nextFreeIndex].parent = current;
                this->nextFreeIndex++;
                this->elements[current].elementsToTheLeft++;
                return;
            }
            this->elements[current].elementsToTheLeft++;
            current = this->elements[current].leftChild;
        }
    }
}

// Theta(n)
void SortedIndexedList::resize() {
    Node *newElems = new Node[this->capacity*2];
    this->capacity *= 2;
    for(int i = this->headOfList; i != this->nextFreeIndex; i++){
        newElems[i].leftChild = this->elements[i].leftChild;
        newElems[i].rightChild = this->elements[i].rightChild;
        newElems[i].elementsToTheLeft = this->elements[i].elementsToTheLeft;
        newElems[i].parent = this->elements[i].parent;
        newElems[i].info = this->elements[i].info;
    }
    this->elements = newElems;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
}
