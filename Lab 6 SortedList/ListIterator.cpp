#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) 
{	
	//Complexity: O(n) - n is the height of the tree
	this->currentValue = NULL_TCOMP;
	this->stackSize = 0;
	this->stack = new Node[list.numberOfValues];
	int current = list.root;
	while (current != -1)
	{
		this->stack[stackSize++] = list.tree[current];
		current = list.tree[current].leftPos;
	}
	if (this->stackSize)
		this->currentValue = stack[stackSize-1].element;
}

void ListIterator::first(){
	//Complexity: O(n) - n is the height of the tree
	this->currentValue = NULL_TCOMP;
	this->stackSize = 0;
	int current = list.root;
	while (current != -1)
	{
		this->stack[stackSize++] = list.tree[current];
		current = list.tree[current].leftPos;
	}
	if (this->stackSize)
		this->currentValue = stack[stackSize - 1].element;
}

void ListIterator::next(){
	//Complexity: O(n)
	if (!valid())
		throw exception("You have reached the end!");
	this->stackSize--;
	Node node = this->stack[stackSize];  // pop
	if (node.rightPos != -1)
	{
		int current = node.rightPos;
		while (current != -1)
		{
			this->stack[stackSize++] = list.tree[current];
			current = list.tree[current].leftPos;
		}
	}
	if (this->stackSize)
		this->currentValue = stack[stackSize - 1].element;
	else
		this->currentValue = NULL_TCOMP;
}

bool ListIterator::valid() const{
	//Complexity: Tetha(1)
	return this->currentValue != NULL_TCOMP;
}

TComp ListIterator::getCurrent() const{
	//Complexity: Tetha(1)
	return this->currentValue;
}

void ListIterator::jumpForward(int k)
{
	//Complexity: BC: O(1), WC: O(n*k), OC: O(n*k)
	if (k<=0 || !valid())
		throw exception("Invalid!");
	while (k)
	{
		this->stackSize--;
		if (this->stackSize < 0)
		{
			this->currentValue = NULL_TCOMP;
			return;
		}
		Node node = this->stack[stackSize];  // pop

		int current = node.rightPos;
		while (current != -1)
		{
			this->stack[stackSize++] = list.tree[current];
			current = list.tree[current].leftPos;
		}
		k--;
	}
	if (this->stackSize)
		this->currentValue = stack[stackSize - 1].element;
	else
		this->currentValue = NULL_TCOMP;
}


