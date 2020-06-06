#include "Matrix.h"

Matrix::Matrix(int nrLines, int nrCols) {
	//Time complexity: O(n)
	this->nrRows = nrLines;
	this->nrCols = nrCols;
	this->columnPointers = new int[nrCols + 1];
	for (int i = 0; i <= nrCols; i++)
		this->columnPointers[i] = 0;
	this->size = 0;
	this->capacity = 8;
	this->rowIdxVal = new TPair[capacity];
}

int Matrix::nrLines() const {
	//Time complexity: O(1)
	return this->nrRows;
}

int Matrix::nrColumns() const {
	//Time complexity: O(1)
	return this->nrCols;
}

TElem Matrix::element(int i, int j) const {
	//Time complexity: O(n)
	if (i < 0 || j < 0 || i >= nrRows || j >= nrCols)
		throw exception("Invalid position!");
	int colStart = columnPointers[j];
	int colEnd = columnPointers[j + 1];
	if (!(colEnd - colStart)) return NULL_TELEM;
	for (int idx = colStart; idx < colEnd; idx++)
		if (this->rowIdxVal[idx].first == i)
			return this->rowIdxVal[idx].second;
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//Time complexity: O(n)
	if (i < 0 || j < 0 || i >= nrRows || j >= nrCols)
		throw exception("Invalid position!");
	TElem previous = element(i, j);
	if (previous != NULL_TELEM)
	{
		if (e == NULL_TELEM)   /// Delete the value
			deleteCase(i, j);
		else /// Replace with the new value
			replaceCase(i, j, e);
	}
	else if (e != NULL_TELEM)  /// Insert the new value
		insertCase(i, j, e);
	return previous;
}

int Matrix::numberOfNonZeroElems(int line) const
{
	///WC : n
	///AC : n
	///BC : n
	if (line < 0 || line >= nrRows)
		throw exception("Invalid line!");
	int contor = 0;
	for (int i = 0; i < size; i++)
		if (rowIdxVal[i].first == line && rowIdxVal[i].second != NULL_TELEM)
			contor++;
	return contor;
}

Matrix::~Matrix()
{
	//Time complexity: O(1)
	delete[] this->columnPointers;
	delete[] this->rowIdxVal;
}

void Matrix::resize(int factor)
{
	//Time complexity: O(n)
	this->capacity *= factor;
	TPair* newPairs = new TPair[this->capacity];
	for (int i = 0; i < this->size; i++)
		newPairs[i] = this->rowIdxVal[i];
	delete[] this->rowIdxVal;
	this->rowIdxVal = newPairs;
}

void Matrix::insertTPair(TPair p, int position)
{
	//Time complexity: O(n)
	if (position < 0 || position > size)
		throw exception("Invalid position!");
	if (size == capacity)
		resize();
	for (int i = size; i > position; i--)
		this->rowIdxVal[i] = this->rowIdxVal[i - 1];
	this->rowIdxVal[position] = p;
	size++;
}

void Matrix::removeTPair(int position)
{
	//Time complexity: O(n)
	if (position < 0 || position > size)
		throw exception("Invalid position!");
	for (int i = position; i < size-1; i++)
		this->rowIdxVal[i] = this->rowIdxVal[i + 1];
	size--;
}

void Matrix::deleteCase(int i, int j)
{
	for (int idx = columnPointers[j]; idx < columnPointers[j + 1]; idx++)
		if (rowIdxVal[idx].first == i)
		{
			removeTPair(idx);
			break;
		}
	for (int idx = j + 1; idx <= this->nrCols; idx++)
		columnPointers[idx]--;
}

void Matrix::replaceCase(int i, int j, TElem e)
{
	for (int idx = columnPointers[j]; idx < columnPointers[j + 1]; idx++)
		if (this->rowIdxVal[idx].first == i)
		{
			this->rowIdxVal[idx].second = e;
			break;
		}
}

void Matrix::insertCase(int i, int j, TElem e)
{
	for (int idx = j + 1; idx <= this->nrCols; idx++)
		columnPointers[idx]++;
	TPair newPair(i, e);
	for (int idx = columnPointers[j]; idx < columnPointers[j + 1] - 1; idx++)
		if (rowIdxVal[idx].first > i)
		{
			insertTPair(newPair, idx);
			return;
		}
	insertTPair(newPair, columnPointers[j + 1] - 1);
}