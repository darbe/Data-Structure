#define STACK_TYPE int
#include<stdlib.h>
//typedef unsigned int size_t;
typedef unsigned int big;

void push(STACK_TYPE value);

void pop(void);

STACK_TYPE top(void);

int is_empty(void);

int is_full(void);

void creat_stack(size_t size);

void destroy_stack(void);
