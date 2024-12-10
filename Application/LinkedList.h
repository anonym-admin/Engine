#pragma once

/*
=============
LinkedList
=============
*/

struct DL_LIST
{
	struct DL_LIST* next;
	struct DL_LIST* prev;
};

void DL_InsertFront(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* newNode);
void DL_InsertBack(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* newNode);
void DL_Delete(DL_LIST** headNode, DL_LIST** tailNode, DL_LIST* delNode);
