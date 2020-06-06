#include <assert.h>
#include "Matrix.h"


using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	pair<int, int> position(1, 1);
	assert(m.positionOf(5) == position);
	position.first = position.second = -1;
	assert(m.positionOf(99) == position);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}