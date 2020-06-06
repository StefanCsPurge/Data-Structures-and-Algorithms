#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	SortedMultiMap& map;
	SMMIterator(SortedMultiMap& map);

	//Representation
	TElem currentElement;
    SortedMultiMap smmCopy;
    int currentNodePos;  // pos of the min head in the table
    int currentArrayPos;
    void findMinHead();
    void removeMinNode();
    void initializeSMMCopy();
    static KeyNode* createNodeCopy(KeyNode* n);
	


public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;

	//removes and returns the current pair from the iterator
    //after the operation the current pair from the Iterator is the next element from the MultiMap, or, if the removed element was the last one, the iterator is invalid
    //throws exception if the iterator is invalid
	TElem remove();
};

