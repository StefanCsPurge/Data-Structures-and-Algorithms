#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
//#define NULL_TKey -11111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
#define ALPHA 0.9  // load factor

struct KeyNode
{
    TKey key;  // unique key motherfucker
    TValue * values;  // dyn array of key, which contains the values, because it'a multimap
    int cap,size;
    KeyNode* next;
};

struct SLLKeys
{  // the hash function gives the same value for the keys stored in this SLL
    KeyNode* head;
};


/// ADT SortedMultiMap: using a hashtable with separate chaining in which
/// unique keys are stored with a dynamic array of the associated values.
class SortedMultiMap {
	friend class SMMIterator;
private:
		int m;   // capacity - number of slots
		int numberOfKeys;   //
		int numberOfValues; // size
		SLLKeys* sllKeys;  // separate chaining style
        Relation rel;

public:

    int hash(TKey k) const { return abs(k % m); }  // h : U -> {0,..m-1}  // this should give the position from keys

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator();

    static void addValueToKey(KeyNode* node, TValue v);

    static void deleteValueFromKeyPosition(KeyNode* node, int position);

    static vector<TValue> getValuesSTLVector(KeyNode* node);

    void resizeTable();

    void displaySMM(const SortedMultiMap& smm);

    // destructor
    ~SortedMultiMap();
};
