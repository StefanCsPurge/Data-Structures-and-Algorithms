#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//Complexity: O(1)
	currentE = bag.head;
	currentF = 0;
}

TComp SortedBagIterator::getCurrent() {
	//Complexity: O(1)
	if(!valid())
		throw exception("You reached the end!");
	return bag.elements[currentE].first;
}

bool SortedBagIterator::valid() {
	//Complexity: O(1)
	if(currentE == -1)
		return false;
	return true;
}

void SortedBagIterator::next() {
	//Complexity: O(1)
	if (!valid())
		throw exception("You reached the end!");
	currentF++;
	if (currentF == bag.elements[currentE].second)
	{
		currentE = bag.next[currentE];
		currentF = 0;
	}
}

void SortedBagIterator::first() {
	//Complexity: O(1)
	currentE = bag.head;
	currentF = 0;
}

