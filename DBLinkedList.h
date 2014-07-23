#ifndef __DB_LINKED_LIST_H__
#define __DB_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef struct _data
{
	int userId;
	char userName[50];
	char userAddress[100];
	char handphone[50];
} LData;

typedef struct _node
{
	LData data;
	struct _node * prev; 
	struct _node * next;
} Node;

typedef struct _dblinkedList
{
	Node * head;
	Node * tail;
	Node * cur;
	int numOfData;
} DBLinkedList;

typedef DBLinkedList List;

// LinkedList 관련 함수
void initList(List * plist);
void LInsert(List * plist, LData * data);

int LFirst(List * plist);
int LNext(List * plist, LData * pdata);
int LPrevious(List * plist, LData * pdata);

LData LRemove(List * plist);
int Lcount(List * plist);

#endif