#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _STACK_ITEM
{
	int d;
	struct _STACK_ITEM* link;
}STACK_ITEM;

STACK_ITEM* root = NULL;

int isEmpty(STACK_ITEM* pStack)
{
	return pStack == NULL ? 1 : 0;
}
int isFull(STACK_ITEM* pStack)
{
	return 0;
}
STACK_ITEM* Push(STACK_ITEM* pStack, int value)
{
	STACK_ITEM* newItem = (STACK_ITEM*)calloc(1, sizeof(STACK_ITEM));
	newItem->d = value;
	newItem->link = pStack;
	return newItem;
}

STACK_ITEM* Pop(STACK_ITEM** ppStack)
{
	STACK_ITEM* pStack = *ppStack;
	
	if (isEmpty(pStack))
		return NULL;
	else
	{
		STACK_ITEM* oldTop = pStack;
		STACK_ITEM* popItem = (STACK_ITEM*)calloc(1, sizeof(STACK_ITEM));
		popItem->d = oldTop->d;
		*ppStack = pStack->link;
		free(oldTop);
		return popItem;
	}
}

void Initialize(STACK_ITEM* pStack)
{
	while (pStack != NULL)
	{
		STACK_ITEM* next = pStack->link;
		free(pStack);
		pStack = next;
	}
	pStack = NULL;
}

