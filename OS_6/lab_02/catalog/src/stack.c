#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "stack.h"
#include "path.h"

Stack *CreateStack()
{
	Stack *res = (Stack *)malloc(sizeof(Stack));
	res->count = 0;
	res->path_arr = NULL;

	return res;
}

void DestroyStack(Stack *stack)
{
	for (int i = 0; i < stack->count; i++)
		DestroyPath(stack->path_arr[i]);

	if (stack->path_arr)
		free(stack->path_arr);
	if (stack)
		free(stack);
}

void Push(Stack *stack, char *elem, int depth)
{
	(stack->count)++;

	if (stack->path_arr)
		stack->path_arr = realloc(stack->path_arr, sizeof(Path *) * stack->count);
	else
		stack->path_arr = malloc(sizeof(Path *));

	stack->path_arr[stack->count - 1] = CreatePath(elem, depth);
}

Path *Pop(Stack *stack)
{
	if (stack->count < 1)
		return NULL;

	Path *res = stack->path_arr[stack->count - 1];

	(stack->count)--;
	stack->path_arr = realloc(stack->path_arr, sizeof(Path *) * stack->count);

	return res;
}

void Output(const Stack const *const stack)
{
	for (int i = 0; i < stack->count; i++)
		printf("%s %d\n", stack->path_arr[i]->name, stack->path_arr[i]->depth);
	puts("");
}

// int main(void)
// {
// 	Stack *begin_path = CreateStack();

// 	Push(begin_path, "aaa");
// 	Push(begin_path, "bbb");
// 	Push(begin_path, "ccc");

// 	Output(begin_path);

// 	char *elem = Pop(begin_path);
// 	printf("elem = %s\n", elem);
// 	free(elem);

// 	Output(begin_path);

// 	DestroyStack(begin_path);

// 	return 0;
// }