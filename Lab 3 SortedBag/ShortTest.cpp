#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

void testAddOccurrences()
{
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(10);
	sb.add(8);
	assert(sb.nrOccurrences(5) == 1);
	sb.addOccurrences(2, 5);
	assert(sb.nrOccurrences(5) == 3);
	sb.addOccurrences(3, 10);
	assert(sb.nrOccurrences(10) == 4);
	cout << "Add occurrences test passed!" << endl;
}

void testRemoveOccurrences()
{
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	assert(sb.nrOccurrences(5) == 2);
	sb.removeOccurrences(2, 5);
	assert(sb.nrOccurrences(5) == 0);
	sb.add(10);
	sb.add(10);
	sb.add(10);
	sb.removeOccurrences(3, 10);
	assert(sb.nrOccurrences(10) == 1);
	cout << "Remove occurrences test passed!" << endl;
}

