#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>


typedef struct _QUEUE_ELEMENT
{
	int data;
	struct _QUEUE_ELEMENT* link;
}QUEUE_ELEMENT, *PQUEUE_ELEMENT;

typedef struct _QUEUE
{
	PQUEUE_ELEMENT Front;
	PQUEUE_ELEMENT Rear;	
	int size;
}QUEUE, *PQUEUE;


int IsEmpty(PQUEUE pQueue)
{
	if (pQueue->Front == NULL && pQueue->Rear == NULL)
		return 1;
	else
		return 0;
}
void Enqueue(PQUEUE pQueue, element_type data)
{
	PQUEUE_ELEMENT newElement = (PQUEUE_ELEMENT)calloc(1, sizeof(QUEUE_ELEMENT));
	newElement->data = data;
	newElement->link = NULL;
	if (IsEmpty(pQueue))
	{
		pQueue->Front = newElement;
		pQueue->Rear = newElement;
	}else{
		pQueue->Rear->link = newElement;
		pQueue->Rear = newElement;
	}
	pQueue->size += 1;
}
int Dequeue(PQUEUE pQueue, element_type* out)
{
	if (IsEmpty(pQueue))
		return 0; //Khong lay duoc
	else
	{
		*out = pQueue->Front->data;
		PQUEUE_ELEMENT oldElement = pQueue->Front;
		pQueue->Front = pQueue->Front->link;
		free(oldElement);
		oldElement = NULL;
		if (pQueue->Front == NULL)
		{
			pQueue->Rear = NULL;
		}
		pQueue->size -= 1;
		return 1; //Lay thanh cong
	}
}
void Free(PQUEUE pQueue)
{
	int d;
	while (Dequeue(pQueue, &d) == 1);
}