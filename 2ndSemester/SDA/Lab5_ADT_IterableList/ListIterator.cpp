#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

// O(n)
void ListIterator::populateStack(int nodIndex) {
    if(this->list.elements[nodIndex].leftChild != -1){
        this->populateStack(this->list.elements[nodIndex].leftChild);
    }
    this->stack[current++] = nodIndex;
    if(this->list.elements[nodIndex].rightChild != -1){
        this->populateStack(this->list.elements[nodIndex].rightChild);
    }
}

//int* ppopulateStack() {
//    int secondStack[2000], *mainStack;
//    mainStack = new int[2000];
//    int top=1, mainTop=0, currentNode;
//    if(!this->list.size()){
//        mainStack[0] = NULL_TCOMP;
//        return mainStack;
//    }
//    secondStack[1] = this->list.headOfList;
//    mainStack[mainTop++] = this->list.headOfList;
//    while (top){
//        currentNode = secondStack[top--];
//        if(this->list.elements[currentNode].rightChild != -1){
//            secondStack[++top] = this->list.elements[currentNode].rightChild;
//            mainStack[mainTop++] = this->list.elements[currentNode].rightChild;
//        }
//        if(this->list.elements[currentNode].leftChild != -1){
//            secondStack[++top] = this->list.elements[currentNode].leftChild;
//            mainStack[mainTop++] = this->list.elements[currentNode].leftChild;
//        }
//    }
//    mainStack[mainTop] = NULL_TCOMP;
//    return mainStack;
//}

// O(n)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    this->stack = new int[20000];
    this->current = 0;
    if(this->list.size())
        this->populateStack(this->list.headOfList);
    this->stack[this->current] = NULL_TCOMP;
    this->current = 0;
}

// O(n)
void ListIterator::first(){
    this->current = 0;
    if(this->list.size())
        this->populateStack(this->list.headOfList);
    this->stack[this->current] = NULL_TCOMP;
    this->current = 0;
}

//O(1)
void ListIterator::next(){
	if(this->stack[this->current] == NULL_TCOMP)
        throw exception();
    this->current++;
}

//O(1)
bool ListIterator::valid() const{
	if(this->stack[this->current] == NULL_TCOMP)
        return false;
	return true;
}

//O(1)
TComp ListIterator::getCurrent() const{
    return this->list.elements[this->stack[this->current]].info;
}


