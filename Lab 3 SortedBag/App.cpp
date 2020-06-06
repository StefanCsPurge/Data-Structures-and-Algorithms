//ADT SortedBag – using a SLLA with (element, frequency) pairs. 
//Pairs are ordered based on a relation between the elements
//linked list on array as a data structure

#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main() {
	testAll();
	testAddOccurrences();
	testAllExtended();
	
	cout << "Test over" << endl;
	system("pause");
}
