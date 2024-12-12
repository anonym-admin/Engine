#include "pch.h"
#include "Application.h"
#include "HashTable.h"

extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
// D3D12 Agility SDK Runtime
extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 614; }
#if defined(_M_AMD64)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\"; }
#endif

/*
==============
Main entry
==============
*/

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	int32 flags = _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flags);
#endif

	Application* app = new Application;
	if (!app->Initialize(true, true)) // app->Initialize(false, false)
	{
		return -1;
	}

	HashTable* hashTable = HT_CreateHashTable(10);
	
	HT_Insert(hashTable, (void*)L"tex01.dds", (void*)L"01");
	HT_Insert(hashTable, (void*)L"tex01.dds", (void*)L"05");
	HT_Insert(hashTable, (void*)L"tex02.dds", (void*)L"02");
	HT_Insert(hashTable, (void*)L"tex03.dds", (void*)L"03");
	HT_Insert(hashTable, (void*)L"tex04.dds", (void*)L"04");
	HT_Insert(hashTable, (void*)L"tex05.dds", (void*)L"05");
	HT_Insert(hashTable, (void*)L"tex06.dds", (void*)L"06");
	HT_Insert(hashTable, (void*)L"tex07.dds", (void*)L"07");

	wchar_t* value = (wchar_t*)HT_Find(hashTable, (void*)L"tex01.dds");
	wprintf_s(L"%s\n", value);
	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex02.dds");
	wprintf_s(L"%s\n", value);
	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex03.dds");
	wprintf_s(L"%s\n", value);
	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex04.dds");
	wprintf_s(L"%s\n", value);
	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex05.dds");
	wprintf_s(L"%s\n", value);
	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex06.dds");
	wprintf_s(L"%s\n", value);

	value = (wchar_t*)HT_Find(hashTable, (void*)L"tex02.dds");
	wprintf_s(L"%s\n", value);

	Bucket* bucket = HT_Delete(hashTable, (void*)L"tex02.dds");
	wprintf_s(L"%s\n", (wchar_t*)bucket->value);
	HT_DestroyBucket(bucket);

	HT_DestroyHashTable(hashTable);



	int32 exitCode = app->RunApplication(); // success return code : 999
	app->CleanUp();
	delete app;

#ifdef _DEBUG
	_ASSERT(_CrtCheckMemory());
#endif

	return exitCode;
}
