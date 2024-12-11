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
	DL_LIST* prevNode = delNode->prev;
	DL_LIST* nextNode = delNode->next;

	// delNode 가 하나 밖에 없을 경우
	if (!prevNode && !nextNode)
	{
		return;
	}
	if (prevNode && nextNode)
	{
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}
	// delNode 가 head 일 경우
	if(!prevNode)
	{
		*headNode = nextNode;
		nextNode->prev = nullptr;
	}
	// delNode 가 tail 일 경우
	if(!nextNode)
	{
		*tailNode = prevNode;
		prevNode->next = nullptr;
	}

	delNode->prev = nullptr;
	delNode->next = nullptr;
}


/*
========
Test
========
*/

class Something
{
public:
	Something()
	{
	}

	int var;
	int var2;
	int var3;
	DL_LIST list;
};

void Test()
{
	DL_LIST* headNode = nullptr;
	DL_LIST* tailNode = nullptr;

	uint32 offset = (uint32)(&((Something*)nullptr)->list) - (uint32)(&((Something*)nullptr)->var);

	Something* s1 = new Something;
	s1->var = 1;
	DL_InsertFront(&headNode, &tailNode, &s1->list);
	Something* s2 = new Something;
	s2->var = 2;
	DL_InsertFront(&headNode, &tailNode, &s2->list);
	Something* s3 = new Something;
	s3->var = 3;
	DL_InsertFront(&headNode, &tailNode, &s3->list);
	Something* s4 = new Something;
	s4->var = 4;
	DL_InsertFront(&headNode, &tailNode, &s4->list);
	Something* s5 = new Something;
	s5->var = 5;
	DL_InsertFront(&headNode, &tailNode, &s5->list);


	DL_LIST* curNode = headNode;
	while (curNode != nullptr)
	{
		Something* s = (Something*)((uint8*)curNode - offset);
		printf("%d ", s->var);

		curNode = curNode->next;
	}
	printf("\n");

	DL_Delete(&headNode, &tailNode, &s3->list);

	curNode = headNode;
	while (curNode != nullptr)
	{
		Something* s = (Something*)((uint8*)curNode - offset);
		printf("%d ", s->var);

		curNode = curNode->next;
	}
}