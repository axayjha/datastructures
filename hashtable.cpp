/**
	Hashtable implementation
	Partially generic:-> works with any numeric or char type

	@author Akshay
*/

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <assert.h>
#include <stdint.h>
#include <string>
using namespace std;

enum { 
	HSIZE = 0xf007,
	ERROR = 0xc001,
};

template <typename key_type, typename item_type> 
class TableNode{
public:
	key_type key;
	item_type item;	
	TableNode(){}
	TableNode(key_type key, item_type item)
	{
		this->key  = key;
		this->item = item;
	}
};

template <typename key_type, typename item_type> 
class HashTable{

	TableNode<key_type, item_type> **table;
public:
	HashTable();
	~HashTable();
	uint64_t hash(item_type key);
	void insert(key_type key, item_type item);
	item_type search(key_type key);
	void remove(key_type key);
};

template <typename key_type, typename item_type>
HashTable <key_type, item_type> :: HashTable() 
{
	this->table = new TableNode<key_type, item_type>* [HSIZE];
	for(int i = 0; i < HSIZE; i++)
		table[i] = NULL;
}

template <typename key_type, typename item_type>
HashTable <key_type, item_type> :: ~HashTable()
{
    for(int i=0; i<HSIZE; ++i)
        if(table[i] != NULL) 
        	delete table[i];        
}

template <typename key_type, typename item_type>
uint64_t HashTable <key_type, item_type> :: hash(item_type key)
{
	return key%HSIZE;
}


template <typename key_type, typename item_type>
void HashTable <key_type, item_type> :: insert(key_type key, item_type item)
{
	uint64_t hashedkey = hash(key);
	while (table[hashedkey] != NULL && table[hashedkey]->key != key)
		hashedkey = hash(hashedkey + 1);
	if (table[hashedkey] != NULL)
		delete table[hashedkey];
	table[hashedkey] = new TableNode<key_type, item_type>(key, item);
}

template <typename key_type, typename item_type>
void HashTable <key_type, item_type> :: remove(key_type key)
{
    uint64_t hashedkey = hash(key);
    while (table[hashedkey] != NULL) {
        if (table[hashedkey]->key == key) break;
        hashedkey = hash(hashedkey+1);
    }

    if (table[hashedkey] == NULL) {
        cout << "No element at the key" << endl;
        return;
    }
    else table[hashedkey] = NULL;
}


template <typename key_type, typename item_type>
item_type HashTable <key_type, item_type> :: search(key_type key)
{
	uint64_t hashedkey = hash(key);
    while (table[hashedkey]!= NULL && table[hashedkey]->key != key)
    	hashedkey = hash(hashedkey+1);
    

    if (table[hashedkey] == NULL) {
        cout << "Nothing found for key "<< key << endl;
        return ERROR;
    }
    return table[hashedkey]->item;
}


int main(int argc, char *argv[])
{
	HashTable<long double, char> H;
	H.insert(4,'a');
	H.insert(5,'b');
	cout << H.search(6) << endl;
	cout << H.search(5) << endl;
	H.remove(5);
	cout << H.search(5) << endl;
	return 0;
}