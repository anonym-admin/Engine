#include "pch.h"
#include "LinkedList.h"

/*
=============
LinkedList
=============
*/

void DL_InsertFront(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* newNode)
{
	if (!*headNode)
	{
		*headNode = *tailNode = newNode;
		(*headNode)->next = nullptr;
		(*headNode)->prev = nullptr;
	}
	else
	{
#if defined(_DEBUG)
		if (*headNode == newNode)
		{
			__debugbreak();
		}
#endif
		newNode->next = *headNode;
		(*headNode)->prev = newNode;
		*headNode = newNode;
		newNode->prev = nullptr;
	}
}

void DL_InsertBack(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* newNode)
{
	if (!*headNode)
	{
		*tailNode = *headNode = newNode;
		(*headNode)->next = nullptr;
		(*tailNode)->prev = nullptr;
	}
	else
	{
		newNode->prev = *tailNode;
		(*tailNode)->next = newNode;
		*tailNode = newNode;
		newNode->next = nullptr;
	}
}

void DL_Delete(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* delNode)
{
	
}
