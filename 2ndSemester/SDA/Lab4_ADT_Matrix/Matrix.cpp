#include "Matrix.h"
#include <exception>
using namespace std;

//O(20) -> O(initialCapacity(2) * separateChainLength(10))
Matrix::Matrix(int nrLines, int nrCols): numberOfLines(nrLines), numberOfColumns(nrCols){
    this->capacity = 2;
    this->elements = new HashElements[this->capacity];
    for(int i = 0; i < 2; i++) {
        this->elements[i].numberOfElements = 0;
        this->elements[i].capacityOfElement = SEPARATE_CHAIN_LENGTH;
        this->elements[i].values = new Entity[SEPARATE_CHAIN_LENGTH];
        for(int j = 0; j < SEPARATE_CHAIN_LENGTH; j++) {
            this->elements[i].values[j].value = NULL_TELEM;
            this->elements[i].values[j].line = -1;
            this->elements[i].values[j].column = -1;
        }
    }
}

//O(1)
TElem Matrix::element(int i, int j) const {
    if(i >= this->nrLines() || j >= this->nrColumns() || i < 0 || j < 0)
        throw exception();
    int exists = this->exist(i,j);
    if (exists == -1)
	    return NULL_TELEM;
    return this->elements[getKey(i, j, this->capacity)].values[exists].value;
}

//Best case: O(1), Worst Case: O(n^2)
TElem Matrix::modify(int i, int j, TElem e) {
    // if the input is incorrect
	if(i >= this->nrLines() || j >= this->nrColumns() || i < 0 || j < 0)
        throw exception();

    // if it exists
    int exists = this->exist(i,j);
    if (exists != -1){
        TElem previousElement = this->elements[getKey(i,j, this->capacity)].values[exists].value;
        this->elements[getKey(i,j, this->capacity)].values[exists].value = e;
        return previousElement;
    }

    // if it doesn't exist
    // if key list is full
    if(this->elements[getKey(i, j, this->capacity)].numberOfElements == this->elements[getKey(i,j, this->capacity)].capacityOfElement)
        this->resize(); // O(n^2)
    int key = this->getKey(i,j, this->capacity);
    this->elements[key].values[this->elements[key].numberOfElements].value = e;
    this->elements[key].values[this->elements[key].numberOfElements].line = i;
    this->elements[key].values[this->elements[key].numberOfElements++].column = j;
    return NULL_TELEM;
}

// Best Case: O(1), Worst Case: O(n), where n is the max length of a separate chain - > in this case O(10)
// -> Worst case: O(10)
int Matrix::exist(int i, int j) const{
    int key = getKey(i, j, this->capacity);
    for(int iter = 0; iter < this->elements[key].numberOfElements; iter++)
        if(this->elements[key].values[iter].line == i && this->elements[key].values[iter].column == j)
            return iter;
    return -1;
}


// O(n^2)
void Matrix::resize() {
    HashElements* newElements = new HashElements[this->capacity*2];
    for(int i = 0; i < this->capacity*2; i++) { // O(capacity*maxSeparate chain)
        newElements[i].numberOfElements = 0;
        newElements[i].capacityOfElement = SEPARATE_CHAIN_LENGTH;
        newElements[i].values = new Entity[SEPARATE_CHAIN_LENGTH];
        for(int j = 0; j < SEPARATE_CHAIN_LENGTH; j++) {
            newElements[i].values[j].value = NULL_TELEM;
            newElements[i].values[j].line = -1;
            newElements[i].values[j].column = -1;
        }
    }
    for(int i = 0; i < this->numberOfLines; i++) // O(nrColumns*nrLines)
        for(int j = 0; j < this->numberOfColumns; j++) {
            int elem = this->element(i, j);
            if(elem == NULL_TELEM)
                continue;
            int newKey = this->getKey(i,j, this->capacity*2);
            newElements[newKey].values[newElements[newKey].numberOfElements].value = elem;
            newElements[newKey].values[newElements[newKey].numberOfElements].line = i;
            newElements[newKey].values[newElements[newKey].numberOfElements++].column = j;
        }
    this->elements = newElements;
    this->capacity *= 2;
}

int Matrix::getKey(int i, int j, int capacity) const{
    return (i * this->nrLines() + j) % capacity;
}

//O(nrCol * (complexity)Modify) -> Best Case: O(nrCol) -> Worst Case: O(nrCol*n^2) -> Worst Case(n^3)
void Matrix::setElemsOnLine(int line, TElem elem) {
    if(line >= this->numberOfLines || line < 0)
        throw exception();
    for(int col = 0; col < this->numberOfColumns; col++)
        this->modify(line, col, elem);
}