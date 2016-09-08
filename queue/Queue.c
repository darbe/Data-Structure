#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Queue.h"


bool InitQueue(LinkQueue *Q)
{
	assert(Q != NULL);
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(Qnode));
	if(Q->front == NULL || Q->rear== NULL)
		return false;
	Q->front->next = NULL;
}

void DestroyQueue(LinkQueue *Q)
{
	assert(Q != NULL);
	while(Q->front != NULL)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

bool QueueEmpty(LinkQueue Q)
{
	assert(Q.front && Q.rear);
	return(Q.front == Q.rear);
}

int QueueLength(LinkQueue Q)
{
	assert(Q.front);
	int length =  0;
	QueuePtr p = Q.front;
	while(p != Q.rear)
	{
		length++;
		p = p->next;
	}
	return length;
}

bool GetHead(LinkQueue Q, ElemType *e)
{
	if(Q.front == Q.rear)
		return false;
	*e = Q.front->next->data;
	return true;
}

void QueueTraverse(LinkQueue Q, void(*fp)(ElemType))
{
	assert(Q.front);
	QueuePtr p = Q.front->next;
	while(p)
	{
		(*fp)(p->data);
		p = p->next;
	}
}

void ClearQueque(LinkQueue *Q)
{
	assert(Q != NULL);
	QueuePtr p = Q->front->next;
	while(p)
	{
		Q->front->next  = p->next;
		free(p);
		p = Q->front->next;
	}

}

bool EnQueue(LinkQueue *Q, ElemType e)
{
	assert(Q != NULL);
	QueuePtr newp = (QueuePtr)malloc(sizeof(Qnode));
	if(newp == NULL)
		return false;
	newp->data = e;
	newp->next = NULL;
	Q->rear->next = newp;
	Q->rear = newp;
	return true;
}

bool DeQueue(LinkQueue *Q, ElemType *e)
{
	assert(Q != NULL);
	if(Q->front == Q->rear)
		return false;
	QueuePtr tmpp = Q->front->next;
	*e = tmpp->data;
	Q->front->next = tmpp->next;

	if(Q->rear == tmpp)
		Q->rear = Q->front;
	
	free(tmpp);
	return true;
}
























