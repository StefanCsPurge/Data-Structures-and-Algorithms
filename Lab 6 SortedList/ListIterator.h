#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	// InOrder iterator
	Node* stack; // stack of size equal to the number of nodes in the tree
	int stackSize;
	TComp currentValue;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;


	//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the List.
    //throws an exception if the iterator is invalid or if k is zero or negative
	void jumpForward(int k);

	//destructor
	~ListIterator() { delete[] stack; }
};


