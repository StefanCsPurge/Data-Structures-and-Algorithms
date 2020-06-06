#pragma once
#include <utility>
#include <exception>
#include <iostream>
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

using namespace std;

typedef pair<int, TElem> TPair;

class Matrix {

private:
	//Representation
	int nrRows, nrCols;
	int* columnPointers; // has an entry for each column, retains the index in rowIdxVal where the given column starts
	TPair* rowIdxVal; // contais the pairs (rowIndex, non-zero elem)
	int size, capacity;

public:
	//constructor
	Matrix(int nrLines=0, int nrCols=0);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the number of non-zero elements from a given line
    //throws an exception if line is not valid
	int numberOfNonZeroElems(int line) const;

	//destructor
	~Matrix();

private:
	void resize(int factor = 2);
	void insertTPair(TPair p, int position);
	void removeTPair(int position);
	void deleteCase(int i, int j);
	void replaceCase(int i, int j, TElem e);
	void insertCase(int i, int j, TElem e);
};
