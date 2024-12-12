#pragma once

#include "LinkedList.h"

/*
==============
Hash Table
==============
*/

struct Bucket
{
	DL_LIST link;
	void* key;
	void* value;
};

struct HashTable
{
	uint32 tableSize;

	DL_LIST** headList;
	DL_LIST** tailList;
};

HashTable* HT_CreateHashTable(uint32 tableSize);
Bucket* HT_CreateBucket(void* key, void* value);
void HT_DestroyHashTable(HashTable* hashTable);
void HT_DestroyBucket(Bucket* bucket);
void HT_Insert(HashTable* hashTable, void* key, void* value);
void* HT_Find(HashTable* hashTable, void* key);
Bucket* HT_Delete(HashTable* hashTable, void* key);
void HT_DeleteAll(HashTable* hashTable);
int32 HT_HashFunc(void* key, uint32 keyLen, uint32 tableSize);


