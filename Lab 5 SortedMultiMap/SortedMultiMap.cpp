#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <vector>
#include <exception>
#include <iostream>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    //Complexity: Tetha(m)
	this->rel = r;
	this->m = 13;
	this->numberOfKeys = 0;
	this->numberOfValues = 0;
	this->sllKeys = new SLLKeys[m];
	for(int i=0;i<m;i++)
        this->sllKeys[i].head = nullptr;
}

void SortedMultiMap::add(TKey c, TValue v) {
    // Complexity: Tetha(n) amortised
    if((double) (numberOfKeys+1.0) / m > ALPHA)
        resizeTable();
    KeyNode* current = this->sllKeys[hash(c)].head;
    KeyNode* prev = nullptr;
    // Find where to insert
    while(current!= nullptr)
    {
        if (current->key == c)
        {
            addValueToKey(current,v);
            this->numberOfValues++;
            return;
        }
        if(!rel(current->key,c))
            break;
        prev = current;
        current = current->next;
    }
    auto* newNode = new KeyNode;  // create and initialise the new node
    newNode->key = c;
    newNode->cap = 4;
    newNode->size = 1;
    newNode->values = new TValue[4];
    newNode->values[0] = v;
    newNode->next = current;
    if(prev == nullptr)  // in case we replace the head we dont have a prev
        sllKeys[hash(c)].head = newNode;
    else prev->next = newNode;
    this->numberOfKeys++;
    this->numberOfValues++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    // Complexity: O(n)
    KeyNode* current = this->sllKeys[hash(c)].head;
    while(current!= nullptr)
    {
        if (current->key == c)
            break;
        if(!rel(current->key,c))
            return vector<TValue>();
        current = current->next;
    }
	return getValuesSTLVector(current);
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    // Complexity: O(n^2)
	KeyNode* current = this->sllKeys[hash(c)].head, *prev = nullptr;
    while(current!= nullptr && rel(current->key,c))
    {
        if (current->key == c)
        {
            for(int i=0;i<current->size;i++)
                    if(current->values[i] == v)
                    {
                        deleteValueFromKeyPosition(current,i);
                        this->numberOfValues--;
                        if(current->size == 0) // remove the entire key
                        {
                            if(prev!= nullptr)
                                prev->next = current->next;
                            else sllKeys[hash(c)].head = current->next;
                            delete[] current->values;
                            delete current;
                            this->numberOfKeys--;
                        }
                        return true;
                    }
            break;
        }
        prev = current;
        current = current->next;
    }
    return false;
}


int SortedMultiMap::size() const {
	return numberOfValues;
}

bool SortedMultiMap::isEmpty() const {
	return numberOfValues==0;
}

SMMIterator SortedMultiMap::iterator() {
	return SMMIterator{*this};
}

SortedMultiMap::~SortedMultiMap() {
	//first free the values dynamic vector from every key, and then the key
	for(int i=0;i<m;i++)
    {
        KeyNode* current = sllKeys[i].head;
        while(current != nullptr)
        {
            KeyNode* next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
	delete[] this->sllKeys;
}

void SortedMultiMap::resizeTable() {
    //Complexity: Tetha(n^2)
    this->m*=2;
    auto* newSllKeys = new SLLKeys[m];
    for(int i=0;i<m;i++)
        newSllKeys[i].head = nullptr;
    for(int i=0;i<m/2;i++)
        {
            KeyNode* current = this->sllKeys[i].head;
            while(current != nullptr)
            {
                int newPos = hash(current->key);  // get hash position in the new table (rehash)
                KeyNode* prev = nullptr;
                KeyNode* newCurrent = newSllKeys[newPos].head;
                while(newCurrent!=nullptr && rel(newCurrent->key,current->key))
                {  // find where to insert in the new table
                    prev = newCurrent;
                    newCurrent = newCurrent->next;
                }
                KeyNode* newNode = current;  // initialise a node in the new table
                if(prev == nullptr)  // in case we replace the head we dont have a prev
                    newSllKeys[newPos].head = newNode;
                else prev->next = newNode;  // change previous's next in the SLL of the new table

                current = current->next; // now get to the next element in the old table
                newNode->next = newCurrent;  // but we have to change the next in the new table

            }
        }
    delete this->sllKeys;
    this->sllKeys = newSllKeys;
}

void SortedMultiMap::addValueToKey(KeyNode *node, TValue v) {
    //Complexity: Tetha(1) amortised
    if(node->size == node->cap)
    {   // resize dynamic vector
        node->cap *= 2;
        auto* newValues = new TValue[node->cap];
        for (int i = 0; i < node->size; i++)
            newValues[i] = node->values[i];
        delete[] node->values;
        node->values = newValues;
    }
    node->values[node->size] = v;
    node->size++;
}

void SortedMultiMap::deleteValueFromKeyPosition(KeyNode* node, int position)
{
    for (int i = position; i < node->size - 1; i++)
        node->values[i] = node->values[i + 1];
    node->size--;
}

vector<TValue> SortedMultiMap::getValuesSTLVector(KeyNode * node)
{
    //Complexity: O(n)
    vector<TValue> v;
    if(node!= nullptr)
        for(int i=0;i<node->size;i++)
           v.push_back(node->values[i]);
    return v;
}

void SortedMultiMap::displaySMM(const SortedMultiMap& smm)
{
    cout << "Keys: " << smm.numberOfKeys << " - Values: " << smm.numberOfValues << endl;
    for (int i = 0; i < smm.m; i++)
    {
        KeyNode* current = smm.sllKeys[i].head;
        if (current)
            cout << "SLL " << i << endl;
        while (current != nullptr)
        {
            cout << "Key " << current->key << " Values: ";
            for (int j = 0; j < current->size; j++)
                cout << current->values[j] << ' ';
            cout << endl;
            current = current->next;
        }
    }
    cout << endl;
}