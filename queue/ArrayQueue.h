#if !defined(DYBAKUBJQYEYE_H)
#define DYBAKUBJQYEYE_H

#include "ElemType.h"
#include "Boolen.h"
typedef struct queue{
	int *pBase;
	int front;
	int rear;
	int maxsize;
}QUEUE,*PQUEUE;

bool InitQueue(PQUEUE Q,int maxsize);
//void DestroyQueue(LinkQueue * Q);
bool QueueEmpty(PQUEUE Q);
//int QueueLength(LinkQueue Q);
//bool GetHead(LinkQueue Q, ElemType *e);
void QueueTraverse(PQUEUE Q, void(*fp)(ElemType));
//void ClearQueue(LinkQueue *Q);
bool EnQueue(PQUEUE Q, ElemType e);
bool DeQueue(PQUEUE Q, ElemType *e);

#endif


