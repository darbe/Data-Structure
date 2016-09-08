#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"ArrayQueue.h"

bool InitQueue(PQUEUE Q, int maxsize){
	Q->pBase = (int *)malloc(sizeof(int)*maxsize);
	if(Q->pBase == NULL){
		printf("Memory allocation failuer");
		return false;
	}
	Q->front = 0;
	Q->rear = 0;
	Q->maxsize = maxsize;
	return true;
}

void QueueTraverse(PQUEUE Q, void(*fp)(ElemType)){
	int i = Q->front;
	while(i % Q->maxsize != Q->rear){
		fp(Q->pBase[i]);
		i++;
	}
}

bool QueueFull(PUEUE Q){
	if(Q->front == (Q->rear+1) % Q->maxsize){
		return true;
	}
	return false;
}

bool QueueEmpty(PQUEUE Q){
	if(Q->front == Q->rear){
		return true;
	}
	return false;
}

bool EnQueue(PQUEUE Q, ElemType e){
	if(QueueFull(Q)){
		return false;
	}
	Q->pBase[Q->rear] = e;
	Q->rear = (Q->rear+1) % Q->maxsize;
	return true;
}

bool DeQueue(PQUEUE Q, ElemType *e){
	if(QueueEmpty(Q)){
		return false;
	}
	*e = Q->pBase[Q->front];
	Q->front = (Q->front+1) % Q->maxsize;
}


