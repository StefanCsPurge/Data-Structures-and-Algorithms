#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>


SortedBag::SortedBag(Relation r) {
	//Complexity: O(n) - where n is the initial capacity
	this->rel = r;
	this->cap = 8;
	this->elements = new TPair[cap];
	this->next = new int[cap];
	this->head = -1;
	for (int i = 0; i < cap - 1; i++)
		this->next[i] = i + 1;
	next[cap - 1] = -1;
	this->firstEmpty = 0;
}

void SortedBag::add(TComp e) {
	//Complexity: O(n)
	int pos = this->head, prev = -1;
	while (pos != -1 && !rel(e, this->elements[pos].first)) // find position to insert
	{
		prev = pos;
		pos = next[pos];
	}
	if (pos != -1 && this->elements[pos].first == e) // element already exists
	{
		this->elements[pos].second++;
		return;
	}
	if (this->firstEmpty == -1)
		this->resizeSLLA();
	pair<TElem, int> newElement(e, 1); // create new element
	int newPos = this->firstEmpty;
	this->elements[newPos] = newElement;
	this->firstEmpty = this->next[firstEmpty];
	this->next[newPos] = pos;
	if(pos == this->head)
		this->head = newPos;
	else
		this->next[prev] = newPos;
}


bool SortedBag::remove(TComp e) {
	//Complexity: O(n)
	int current = this->head, prev = -1;
	while (current != -1 && this->elements[current].first != e)
	{
		if (!rel(this->elements[current].first, e)) // it was not found in the sorted bag, stop earlier
			return false;
		prev = current;
		current = next[current];
	}
	if (current != -1)
	{
		this->elements[current].second--;
		if (this->elements[current].second == 0)
		{
			if (current == this->head)
				this->head = this->next[head];
			else
				this->next[prev] = this->next[current];
			this->next[current] = this->firstEmpty;
			this->firstEmpty = current;
		}
		return true;
	}
	return false;
}


bool SortedBag::search(TComp elem) const {
	//Complexity: O(n)
	int current = this->head;
	while (current != -1 && this->elements[current].first != elem)
	{
		if (!rel(this->elements[current].first, elem)) // it was not found in the sorted bag, stop earlier
			return false;
		current = next[current];
	}
	if (current != -1)
		return true;
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//Complexity: O(n)
	int current = this->head;
	while (current != -1)
	{
		if (!rel(this->elements[current].first, elem))
			break;
		if (this->elements[current].first == elem)
			return this->elements[current].second;
		current = next[current];
	}
	return 0;
}


int SortedBag::size() const {
	//Complexity: O(n)
	int size = 0, current = this->head;
	while (current != -1)
	{
		size += this->elements[current].second;
		current = next[current];
	}
	return size;
}


bool SortedBag::isEmpty() const {
	//Complexity: O(1)
	return this->head == -1;
}


SortedBagIterator SortedBag::iterator() const {
	// Complexity: O(1)
	return SortedBagIterator(*this);
}

void SortedBag::addOccurrences(int nr, TElem elem)
{
	//BC: O(1)
	//WC: O(n)
	//AC: O(n)
	if (nr < 0)
		throw exception("Number of occurences is negative!");
	int pos = this->head, prev = -1;
	while (pos != -1 && !rel(elem, this->elements[pos].first)) // find position to insert
	{
		prev = pos;
		pos = next[pos];
	}
	if (pos != -1 && this->elements[pos].first == elem) // element already exists, add nr to frequency
	{
		this->elements[pos].second += nr;
		return;
	}
	if (this->firstEmpty == -1)
		this->resizeSLLA();
	pair<TElem, int> newElement(elem, nr); // create new element with nr freqeuency
	int newPos = this->firstEmpty;
	this->elements[newPos] = newElement;
	this->firstEmpty = this->next[firstEmpty];
	this->next[newPos] = pos;
	if (pos == this->head)
		this->head = newPos;
	else
		this->next[prev] = newPos;
}

int SortedBag::removeOccurrences(int nr, TElem elem)
{
	//BC: O(1)
	//WC: O(n)
	//AC: O(n)
	if (nr < 0)
		throw exception("Number of occurences is negative!");
	int removedTimes = 0, current = this->head, prev = -1;
	while (current != -1)
	{
		if (!rel(this->elements[current].first, elem)) // it was not found in the sorted bag, stop earlier
			break;
		if (this->elements[current].first == elem)
		{
			removedTimes = this->elements[current].second;
			if (removedTimes > nr)							// set how many times it will be removed
				removedTimes = nr;
			this->elements[current].second -= removedTimes; 
			
			if (this->elements[current].second == 0)    // delete it if occurences becomes 0
			{
				if (current == this->head)
					this->head = this->next[head];
				else
					this->next[prev] = this->next[current];
				this->next[current] = this->firstEmpty;
				this->firstEmpty = current;
			}
			break;
		}
		prev = current;
		current = this->next[current];
	}
	return removedTimes;
}

SortedBag::~SortedBag() {
	//Complexity: O(1)
	delete elements;
	delete next;
}


void SortedBag::resizeSLLA()
{
	//Complexity: O(n)
	TPair* newElems = new TPair[cap * 2];

	int* newNext = new int[cap * 2];
	for (int i = 0; i < cap; i++)
	{
		newElems[i] = this->elements[i];
		newNext[i] = this->next[i];
	}
	for (int i = cap; i < cap * 2 - 1; i++)
		newNext[i] = i + 1;
	newNext[cap * 2 - 1] = -1;
	delete this->elements;
	delete this->next;
	this->elements = newElems;
	this->next = newNext;
	this->firstEmpty = cap;
	this->cap *= 2;
}