#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

SMMIterator::SMMIterator(SortedMultiMap& d) : map(d), smmCopy(SortedMultiMap(d.rel))
{   // Complexity: O(n^2)
    this->initializeSMMCopy();
    if (smmCopy.numberOfKeys)
    {
        this->currentNodePos = 0;
        this->currentArrayPos = 0;
        this->findMinHead(); // set the current node to min head
        this->currentElement.first = smmCopy.sllKeys[currentNodePos].head->key;
        this->currentElement.second = smmCopy.sllKeys[currentNodePos].head->values[0];
        this->currentArrayPos = 1;
    }
}

void SMMIterator::first(){
    // Complexity: O(n^2)
    this->initializeSMMCopy();
    if(!valid()) return;
    this->findMinHead();
    this->currentElement.first = smmCopy.sllKeys[currentNodePos].head->key;
    this->currentElement.second = smmCopy.sllKeys[currentNodePos].head->values[0];
    this->currentArrayPos = 1;
}

void SMMIterator::next(){
    //Complexity: O(n)
    if(!valid()) throw exception("You have reached the end!");
	if(currentArrayPos >= smmCopy.sllKeys[currentNodePos].head->size)
    {
	    this->removeMinNode();
        this->findMinHead();
        if(!smmCopy.numberOfKeys) return;
        this->currentArrayPos = 0;
    }
    this->currentElement.first = smmCopy.sllKeys[currentNodePos].head->key;
    this->currentElement.second = smmCopy.sllKeys[currentNodePos].head->values[currentArrayPos];
	currentArrayPos++;
	smmCopy.numberOfValues--;
}

bool SMMIterator::valid() const{
    //Complexity: O(1)
	return smmCopy.numberOfKeys > 0;
}

TElem SMMIterator::getCurrent() const{
    //Complexity: O(1)
    if(!valid())
            throw exception("You have reached the end!");
	return currentElement;
}

TElem SMMIterator::remove()
{
    //Complexity: BC: O(1) , AC: O(n^2), WC: O(n^2)
    if (!valid())
        throw exception("Invalid iterator!");
    TElem saveCurrent = this->currentElement;
    this->map.remove(currentElement.first, currentElement.second);
    this->next();
	return saveCurrent;
}

void SMMIterator::findMinHead() {
    //Complexity: O(n)
    currentNodePos=0;
    while(currentNodePos<smmCopy.m && smmCopy.sllKeys[currentNodePos].head== nullptr)
        currentNodePos++;
    for(int i=0;i<smmCopy.m;i++)
        if (smmCopy.sllKeys[i].head != nullptr)
        {
            if(! smmCopy.rel(smmCopy.sllKeys[currentNodePos].head->key,smmCopy.sllKeys[i].head->key))
                    currentNodePos = i;
        }
}

void SMMIterator::removeMinNode() {
    //Complexity: O(n)
    auto* nextNode = createNodeCopy(smmCopy.sllKeys[currentNodePos].head->next);
    delete[] smmCopy.sllKeys[currentNodePos].head->values;
    delete smmCopy.sllKeys[currentNodePos].head;
    smmCopy.sllKeys[currentNodePos].head = nextNode;
    smmCopy.numberOfKeys--;
}

void SMMIterator::initializeSMMCopy() {
    //Complexity: O(n^2)
    for (int i = 0; i < smmCopy.m; i++)
    {
        if (smmCopy.sllKeys[i].head)
            delete[] smmCopy.sllKeys[i].head->values;
        delete smmCopy.sllKeys[i].head;
    }
    delete[] smmCopy.sllKeys;
    smmCopy.numberOfKeys = map.numberOfKeys;
    smmCopy.m = map.m;
    smmCopy.sllKeys = new SLLKeys[map.m];
    for(int i=0;i<map.m;i++)
        this->smmCopy.sllKeys[i].head = createNodeCopy(map.sllKeys[i].head);
}

KeyNode* SMMIterator::createNodeCopy(KeyNode* n)
{
    //Complexity: O(n)
    if(n == nullptr)
        return nullptr;
    auto* Copy = new KeyNode;
    Copy->key = n->key;
    Copy->values = new TValue[n->cap];
    for(int i=0;i<n->size;i++)
        Copy->values[i] = n->values[i];
    Copy->cap = n->cap;
    Copy->size = n->size;
    Copy->next = n->next;
    return Copy;
}

