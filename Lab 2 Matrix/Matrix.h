#pragma once
#include <exception>
#include <iostream>
using namespace std;
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct Node {
	TElem value;
	int row, column;
	Node* next; // Pointer to next node in DLL 
	Node* prev; // Pointer to previous node in DLL 
};

class Matrix {

private:
	int colsNum, rowsNum;
	Node* head;
	Node* tail;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

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

	//returns the position of element elem from the Matrix (as a line, column pair). 
	//If elem occurs multiple times, any position where it appears is fine. 
	//If elem is not in the Matrix, returns the pair <-1, -1>
	pair<int, int> positionOf(TElem elem) const;

	//destructor
	~Matrix();

private:
	void deleteCase(int i, int j);
	void replaceCase(int i, int j, TElem e);
	void insertCase(int i, int j, TElem e);
};
