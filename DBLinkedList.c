#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void initList(List * plist)
{
	plist->head = NULL;
	plist->tail = NULL;
	plist->cur = NULL;
	plist->numOfData = 0;
}

void LInsert(List * plist, LData * data)
{
	if (Lcount(plist) == 0)
	{
		plist->head = (Node*)malloc(sizeof(Node));
		plist->tail = plist->head;
		plist->head->data = *data;
	
		Node * dummyNode = (Node*)malloc(sizeof(Node));
		dummyNode->prev = plist->tail;
		plist->tail->next = dummyNode;

		dummyNode->next = (Node*)NULL;
		plist->head->prev = (Node*)NULL;
		
		plist->numOfData++;
	}
	else if (Lcount(plist) > 0)
	{
		Node * newNode = (Node*)malloc(sizeof(Node));
		newNode->data = *data;
		newNode->next = plist->tail->next;
		newNode->prev = plist->tail;

		plist->tail->next->prev = newNode;
		plist->tail->next = newNode;
		plist->tail = newNode;
		plist->numOfData++;
	}
}

int LFirst(List * plist)
{
	if (Lcount(plist) == 0)
	{
		return FALSE;
	}
	else if (Lcount(plist) > 0)
	{
		plist->cur = plist->head;
		return TRUE;
	}
	else
	{
		puts("Error: Lcount(plist) < 0");
		return FALSE;
	}
}

int LNext(List * plist, LData * pdata)
{
	if (plist->cur == NULL || plist->cur->next == NULL)
		return FALSE;

	*pdata = plist->cur->data;
	plist->cur = plist->cur->next;

	return TRUE;
}

int LPrevious(List * plist, LData * pdata)
{
	if (plist->cur == NULL)
		return FALSE;

	*pdata = plist->cur->data;
	plist->cur = plist->cur->prev;

	return TRUE;
}

LData LRemove(List * plist)
{		
	LData rdata = { 0 };

	if (plist->numOfData == 0 || plist->cur == NULL)
		return rdata;

	Node * delNode = plist->cur;

	if (delNode == plist->head)
	{
		plist->head = plist->cur->next;
		plist->head->prev = (Node*)NULL;
	}
	else
	{
		if((plist->cur->next) != NULL) plist->cur->next->prev = plist->cur->prev;
		if((plist->cur->prev) != NULL) plist->cur->prev->next = plist->cur->next;

		plist->cur = plist->cur->prev;
	}

	free(delNode);
	(plist->numOfData)--;
	return rdata;
}

int Lcount(List * plist)
{
	return plist->numOfData;
}
