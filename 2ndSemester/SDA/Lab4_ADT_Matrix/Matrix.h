#pragma once
#define SEPARATE_CHAIN_LENGTH 10

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct Entity{
    int line, column;
    TElem value;
};

struct HashElements{
    Entity* values;
    int capacityOfElement;
    int numberOfElements;
};

class Matrix {

private:
	//TODO - Representation
    int numberOfLines, numberOfColumns;
    int capacity;
    HashElements* elements;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
    int nrLines() const{return this->numberOfLines;}

	//returns the number of columns
    int nrColumns() const{return this->numberOfColumns;}

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);
    // returns the position of i,j if it exists, -1 else
    int exist(int i, int j)const;
    int getKey(int i, int j, int capacity)const;
    void resize();

    void setElemsOnLine(int line, TElem elem);
};
