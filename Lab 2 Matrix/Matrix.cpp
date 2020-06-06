#include "Matrix.h"


Matrix::Matrix(int nrLines, int nrCols) {
	//Time complexity: O(1)
	this->rowsNum = nrLines;
	this->colsNum = nrCols;
	this->head = NULL;
	this->tail = NULL;
}

Matrix::~Matrix()
{
	//Time complexity: O(n)
	Node* current = head;
	while (current != NULL)
	{
		Node* next = current->next;
		if (current == tail)
		delete current; 
		current = next;
	}
}

int Matrix::nrLines() const {
	//Time complexity: O(1)
	return this->rowsNum;
}


int Matrix::nrColumns() const {
	//Time complexity: O(1)
	return this->colsNum;
}


TElem Matrix::element(int i, int j) const {
	//Time complexity: O(n)
	if (i < 0 || j < 0 || i >= rowsNum || j >= colsNum)
		throw exception("Invalid position!");
	Node *current = head;
	while (current != NULL)
	{
		if (current->row == i && current->column == j)
			return current->value;
		current = current->next;
	}
	return NULL_TELEM;
}

pair<int, int> Matrix::positionOf(TElem elem) const
{
	//BC: O(1)
	//AC: O(n)
	//WC: O(n)
	Node* current = this->head;
	while (current != NULL)
	{
		if (current->value == elem)
		{
			pair<int, int> row_col(current->row, current->column);
			return row_col;
		}
		current = current->next;
	}
	pair<int, int> noPosition(-1, -1);
	return noPosition;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//Time complexity: O(n)
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


void Matrix::deleteCase(int i, int j)
{
	Node* current = head;
	while (current != NULL)
	{
		if (current->row == i && current->column == j)
		{
			if (current->prev == NULL) // head case
			{
				Node* nextNode = current->next;
				nextNode->prev = NULL;
				this->head = nextNode;
			}
			else if (current->next == NULL) // tail case
			{
				Node* prevNode = current->prev;
				prevNode->next = NULL;
				this->tail = prevNode;
			}
			else // general case
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
			}
			delete current;
			return;
		}
		current = current->next;
	}
}


void Matrix::replaceCase(int i, int j, TElem e)
{
	
	Node* current = head;
	while (current != NULL)
	{
		if (current->row == i && current->column == j)
		{
			current->value = e;
			return;
		}
		current = current->next;
	}
}

void Matrix::insertCase(int i, int j, TElem e)
{
	Node* newNode = new Node;
	newNode->value = e;
	newNode->row = i;
	newNode->column = j;
	Node* current = this->head;

	// Find where to insert
	while (current!=NULL && current->row < i)
		current = current->next;
	while(current != NULL && current->row == i && current->column<j)
		current = current->next;

	if (current == this->head)  // head case
	{
		newNode->next = head;
		newNode->prev = NULL;
		if(head!=NULL)
			head->prev = newNode;
		this->head = newNode;
	}
	else if (current == NULL) // tail case
	{
		if (tail == NULL)
			tail = head;
		newNode->prev = tail;
		newNode->next = NULL;
		tail->next = newNode;
		this->tail = newNode;
	}
	else // general case
	{
		newNode->prev = current->prev;
		newNode->next = current;
		current->prev->next = newNode;
		current->prev = newNode;
	}
}

