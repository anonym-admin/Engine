#include "pch.h"
#include "HashTable.h"

/*
==============
Hash Table
==============
*/

HashTable* HT_CreateHashTable(uint32 tableSize)
{
	HashTable* hashTable = new HashTable;
	hashTable->headList = new DL_LIST * [tableSize];
	hashTable->tailList = new DL_LIST * [tableSize];
	hashTable->tableSize = tableSize;

	memset(hashTable->headList, 0, sizeof(DL_LIST*) * tableSize);
	memset(hashTable->tailList, 0, sizeof(DL_LIST*) * tableSize);

	return hashTable;
}

Bucket* HT_CreateBucket(void* key, void* value)
{
	Bucket* bucket = new Bucket;
	bucket->key = key;
	bucket->value = value;
	return bucket;
}

void HT_DestroyHashTable(HashTable* hashTable)
{
	if (hashTable)
	{
		HT_DeleteAll(hashTable);

		if (hashTable->tailList)
		{
			delete[] hashTable->tailList;
			hashTable->tailList = nullptr;
		}
		if (hashTable->headList)
		{
			delete[] hashTable->headList;
			hashTable->headList = nullptr;
		}
		delete hashTable;
		hashTable = nullptr;
	}
}

void HT_DestroyBucket(Bucket* bucket)
{
	if (bucket)
	{
		delete bucket;
		bucket = nullptr;
	}
}

void HT_Insert(HashTable* hashTable, void* key, void* value)
{
	wchar_t* keyData = reinterpret_cast<wchar_t*>(key);
	uint32 keyLen = static_cast<uint32>(wcslen(keyData));
	uint32 tableSize = hashTable->tableSize;

	int32 hashValue = HT_HashFunc(key, keyLen, tableSize);
	if (hashValue < 0)
	{
		__debugbreak();
	}

	Bucket* newBucket = HT_CreateBucket(key, value);

	DL_InsertBack(&hashTable->headList[hashValue], &hashTable->tailList[hashValue], &newBucket->link);
}

void* HT_Find(HashTable* hashTable, void* key)
{
	wchar_t* keyData = reinterpret_cast<wchar_t*>(key);
	uint32 keyLen = static_cast<uint32>(wcslen(keyData));
	uint32 tableSize = hashTable->tableSize;

	int32 hashValue = HT_HashFunc(key, keyLen, tableSize);
	if (hashValue < 0)
	{
		__debugbreak();
	}

	DL_LIST* cur = hashTable->headList[hashValue];
	Bucket* bucket = nullptr;
	while (cur != nullptr)
	{
		bucket = reinterpret_cast<Bucket*>(cur);
		wchar_t* originKey = reinterpret_cast<wchar_t*>(bucket->key);
		
		if (!wcscmp(originKey, keyData))
		{
			break;
		}

		cur = cur->next;
	}

	if (!cur)
	{
		// Not find.
#if defined(_DEBUG)
		__debugbreak();
#endif
		return nullptr;
	}

	return bucket->value;
}

Bucket* HT_Delete(HashTable* hashTable, void* key)
{
	wchar_t* keyData = reinterpret_cast<wchar_t*>(key);
	uint32 keyLen = static_cast<uint32>(wcslen(keyData));
	uint32 tableSize = hashTable->tableSize;

	int32 hashValue = HT_HashFunc(key, keyLen, tableSize);
	if (hashValue < 0)
	{
		__debugbreak();
	}

	DL_LIST* cur = hashTable->headList[hashValue];
	Bucket* bucket = nullptr;
	while (cur != nullptr)
	{
		DL_LIST* next = cur->next;
		bucket = reinterpret_cast<Bucket*>(cur);
		wchar_t* originKey = reinterpret_cast<wchar_t*>(bucket->key);

		if (!wcscmp(originKey, keyData))
		{
			DL_Delete(&hashTable->headList[hashValue], &hashTable->tailList[hashValue], cur);
			break;
		}

		cur = next;
	}

	return bucket;
}

void HT_DeleteAll(HashTable* hashTable)
{
	for (uint32 i = 0; i < hashTable->tableSize; i++)
	{
		DL_LIST* cur = hashTable->headList[i];
		Bucket* bucket = nullptr;
		while (cur != nullptr)
		{
			DL_LIST* next = cur->next;
			bucket = reinterpret_cast<Bucket*>(cur);

			DL_Delete(&hashTable->headList[i], &hashTable->tailList[i], cur);
			HT_DestroyBucket(bucket);

			cur = next;
		}
	}
}

int32 HT_HashFunc(void* key, uint32 keyLen, uint32 tableSize)
{
	int32 hashValue = 0;

	wchar_t* keyData = reinterpret_cast<wchar_t*>(key);
	for (uint32 i = 0; i < keyLen; i++)
	{
		hashValue = (hashValue << 3) + keyData[i];
	}

	hashValue %= tableSize;

	return hashValue;
}
