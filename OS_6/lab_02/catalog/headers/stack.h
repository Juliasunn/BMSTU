#ifndef _STACK_H_

#define _STACK_H_

#include "path.h"

typedef struct
{
	int count;
	Path **path_arr;
} Stack;

Stack *CreateStack();

void DestroyStack(Stack *stack);

void Push(Stack *stack, char *elem, int depth);

Path *Pop(Stack *stack);

void Output(const Stack const *const stack);

#endif