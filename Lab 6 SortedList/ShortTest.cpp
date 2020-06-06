#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testRemoveAll()
{
    SortedIndexedList list = SortedIndexedList(relation1);
    assert(list.removeAll() == 0);
    list.add(1);
    assert(list.removeAll() == 1);
    list.add(2);
    list.add(3);
    assert(list.removeAll() == 2);
    assert(list.size() == 0);
    cout << "Remove all tests passed!" << endl;
}

void testJumpForward()
{
    SortedIndexedList list = SortedIndexedList(relation1);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    ListIterator iterator = list.iterator();
    try
    {
        iterator.jumpForward(0);
        assert(false);
        iterator.jumpForward(-1);
        assert(false);
    }
    catch (exception&)
    {
        assert(true);
    }
    iterator.jumpForward(1);
    assert(iterator.getCurrent() == 2);
    iterator.jumpForward(2);
    assert(iterator.getCurrent() == 4);
    iterator.jumpForward(6);
    assert(iterator.valid() == false);
    cout << "Iterator jumpForward tests passed!" << endl;
}