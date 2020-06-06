#include <cassert>
#include "Matrix.h"


void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
}

void testNumberOfNonZeroElems()
{
	Matrix m(5, 5);
	m.modify(1, 2, 900);
	m.modify(1, 4, 9999);
	assert(m.numberOfNonZeroElems(2) == 0);
	assert(m.numberOfNonZeroElems(1) == 2);
	try {
		m.numberOfNonZeroElems(999);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
}