#include "ListIterator.h"
#include "SortedIndexedList.h"
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	//Complexity: O(n)
	this->rel = r;
	this->root = -1;
	this->numberOfValues = 0;
	this->firstEmpty = 0;
	this->capacity = 8;
	this->tree = new Node[8];
	for (int i = 0; i < capacity - 1; i++)
		this->tree[i].leftPos = i + 1;  // use the left array to create a singly linked list of empty positions
	this->tree[capacity - 1].leftPos = -1;
}

int SortedIndexedList::size() const {
	//Complexity: O(1)
	return this->numberOfValues;
}

bool SortedIndexedList::isEmpty() const {
	//Complexity: O(1)
	return this->numberOfValues == 0;
}

TComp SortedIndexedList::getElement(int i) const{
	//Complexity: O(n) - where n is the height of the tree
	if (i < 0 || i >= this->numberOfValues)
		throw exception("Invalid position!");
	int current = this->root;
	while (this->tree[current].leftElements != i)
	{
		if (i < this->tree[current].leftElements)
			current = this->tree[current].leftPos;
		else
		{
			i -= (this->tree[current].leftElements + 1);
			current = this->tree[current].rightPos;
		}
	}
	return this->tree[current].element;
}

TComp SortedIndexedList::remove(int i) {
	//Complexity: O(n)
	if (i < 0 || i >= this->numberOfValues)
		throw exception("Invalid position!");
	int current = this->root, parent = -1;
	while (this->tree[current].leftElements != i)  // find the node to delete
	{
		parent = current;
		if (i < this->tree[current].leftElements)
		{
			this->tree[current].leftElements--;  // decrement the number of nodes from the left subtree of this node
			current = this->tree[current].leftPos;
		}
		else
		{
			i -= (this->tree[current].leftElements + 1);
			current = this->tree[current].rightPos;
		}
	}
	TComp removedElement = this->tree[current].element;  // save the element which will be removed

	if (this->tree[current].leftPos == -1 && this->tree[current].rightPos == -1)  // the node has no descendant
	{
		this->removeNode(current, parent, -1);
	}
	else if (this->tree[current].rightPos == -1)   // the node has only one descendant on left
	{
		this->removeNode(current, parent, this->tree[current].leftPos);
	}
	else if (this->tree[current].leftPos == -1)   // the node has only one descendant on right
	{
		this->removeNode(current, parent, this->tree[current].rightPos);
	}
	else   // the node has 2 descendants
	{
		// find the minimum of the right subtree, move it to the node to be deleted, and delete the minimum
		int minPos = this->tree[current].rightPos, minParent = current;
		this->tree[minPos].leftElements--;
		while (this->tree[minPos].leftPos != -1)
		{
			minParent = minPos;
			minPos = this->tree[minPos].leftPos;
			this->tree[minPos].leftElements--;
		}
		this->tree[current].element = this->tree[minPos].element; // move the minimum 
		this->removeNode(minPos, minParent, this->tree[minPos].rightPos); // delete the minimum
	}
	this->numberOfValues--;
	return removedElement;
}

void SortedIndexedList::removeNode(int nodePos, int parentPos, int nodeChildPos)
{
	if (nodePos == this->root)
		this->root = nodeChildPos;
	else if (nodePos == this->tree[parentPos].leftPos)
		this->tree[parentPos].leftPos = nodeChildPos;
	else
		this->tree[parentPos].rightPos = nodeChildPos;
	this->tree[nodePos].leftPos = this->firstEmpty;
	this->firstEmpty = nodePos;
}

int SortedIndexedList::search(TComp e) const {
	//Complexity: O(n) - where n is the height of the tree
	if (this->root == -1) return -1;
	int foundPosition = -1, listPosition = 0;
	int current = this->root;
	while (current != -1)
	{
		if (this->tree[current].element == e)
			foundPosition = listPosition + this->tree[current].leftElements;
		if (this->rel(e, tree[current].element))
			current = this->tree[current].leftPos;
		else
		{
			listPosition += this->tree[current].leftElements + 1;
			current = this->tree[current].rightPos;
		}
	}
	return foundPosition;
}

void SortedIndexedList::add(TComp e) {
	//Complexity: O(n)
	if (this->firstEmpty == -1)
		this->resizeTreeArray();

	int current = this->root, parent = -1;
	while (current != -1)   // find where to insert the node
	{
		parent = current;
		if (this->rel(e, tree[current].element))
		{
			this->tree[current].leftElements++;
			current = this->tree[current].leftPos;
		}
		else
			current = this->tree[current].rightPos;
	}

	int newPosition = this->firstEmpty;
	if (current == this->root) // there was no node in the tree, so add the root
		this->root = newPosition;
	else if (rel(e, tree[parent].element))
		this->tree[parent].leftPos = newPosition;
	else
		this->tree[parent].rightPos = newPosition;

	this->firstEmpty = this->tree[firstEmpty].leftPos;  // get new firstEmpty position
	
	this->tree[newPosition].element = e;
	this->tree[newPosition].leftElements = 0;
	this->tree[newPosition].leftPos = -1;  // new node does not have children
	this->tree[newPosition].rightPos = -1;
	this->numberOfValues++;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//Complexity: O(1)
	delete[] this->tree;
}

void SortedIndexedList::resizeTreeArray()
{
	//Complexity: O(n)
	Node* newTree = new Node[capacity * 2];
	for (int i = 0; i < capacity; i++)
		newTree[i] = this->tree[i];

	for (int i = capacity; i < capacity * 2 - 1; i++)
		newTree[i].leftPos = i + 1;
	newTree[capacity * 2 - 1].leftPos = -1;
	delete this->tree;
	this->tree = newTree;
	this->firstEmpty = capacity;
	this->capacity *= 2;
}

int SortedIndexedList::removeAll()
{
	//Complexity: Tetha(capacity)
	delete[] this->tree;
	this->root = -1;
	this->firstEmpty = 0;
	this->capacity = 8;
	this->tree = new Node[8];
	for (int i = 0; i < capacity - 1; i++)
		this->tree[i].leftPos = i + 1;
	this->tree[capacity - 1].leftPos = -1;
	int removedElements = this->numberOfValues;
	this->numberOfValues = 0;
	return removedElements;
}

void SortedIndexedList::printList()
{
		for (int i = 0; i < this->size(); i++)
			cout << this->getElement(i) << ' ';
		cout << endl;
}