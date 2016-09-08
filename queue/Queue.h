#if !defined(DYBAKUBJQYEYE_H)
#define DYBAKUBJQYEYE_H

#include "ElemType.h"
#include "Boolen.h"
typedef struct Node{
	ElemType data;
	struct Node * next;
}Qnode, *QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

typedef struct queue{
	int *pBase;
	int front;
	int rear;
	int mmaxsize;
}QUEUE,*PQUEUE;

bool InitQueue(LinkQueue *Q);
void DestroyQueue(LinkQueue * Q);
bool QueueEmpty(LinkQueue Q);
int QueueLength(LinkQueue Q);
bool GetHead(LinkQueue Q, ElemType *e);
void QueueTraverse(LinkQueue Q, void(*fp)(ElemType));
void ClearQueue(LinkQueue *Q);
bool EnQueue(LinkQueue *Q, ElemType e);
bool DeQueue(LinkQueue *Q, ElemType *e);

#endif


