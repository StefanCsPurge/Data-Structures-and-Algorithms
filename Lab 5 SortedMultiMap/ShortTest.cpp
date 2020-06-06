#include <cassert>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
    return cheie1 <= cheie2;
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v=smm.search(3);
    assert(v.empty());

   SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
        it.getCurrent();
    	it.next();
    }

    assert(smm.remove(1, 2));
    assert(smm.remove(1, 3));
    assert(!smm.remove(2, 1));
    assert(smm.isEmpty());
}

void testIteratorRemove()
{
    SortedMultiMap smm = SortedMultiMap(relation1);
    SMMIterator it = smm.iterator();
    try
    {
        it.remove();
        assert(false);
    }
    catch (exception&)
    {
        assert(true);
    }
    smm.add(1, 2);
    smm.add(1, 3);
    smm.add(3, 3);
    smm.add(4, 3);
    SMMIterator it2 = smm.iterator();
    assert(it2.remove() == TElem(1, 2));
    assert(it2.getCurrent() == TElem(1, 3));
    assert(smm.search(1).size() == 1);
    assert(it2.remove() == TElem(1, 3));
    assert(smm.search(1).empty());
    assert(it2.getCurrent() == TElem(3, 3));
    it2.next();
    assert(it2.getCurrent() == TElem(4, 3));
    assert(it2.remove() == TElem(4, 3));
    try
    {
        it2.remove();
        assert(false);
    }
    catch (exception&)
    {
        assert(true);
    }
    cout << "Iterator remove test passed!" << endl;
}