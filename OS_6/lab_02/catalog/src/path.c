#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"

Path *CreatePath(char *name, int depth)
{
	Path *res = (Path *)malloc(sizeof(Path));
	res->name = malloc(sizeof(char) * strlen(name) + 1);
	strcpy(res->name, name);
	res->depth = depth;

	return res;
}

void DestroyPath(Path *path)
{
	if (path->name)
		free(path->name);
	if (path)
		free(path);
}

void ExpandPath(Path *path, char *filename, int curr_len)
{
	path->name = (char *)realloc(path->name, curr_len + strlen(filename) + 2); // +2 == +1 +1 == +'/' +'\0'
	path->name[curr_len] = '/';
	strcpy(&path->name[curr_len + 1], filename);
}

void OutputPath(char *name, int depth, char const symbol)
{
        
        for (int i = 0; i < (depth-1) * 4; i++)
		putchar(' ');
	putchar('|');	
	for (int i = 0; i < 4; i++)
		putchar(symbol);
	printf(" %s\n", name);
}

// int main()
// {
// 	char *a = malloc(sizeof(char) * 5);
// 	strcpy(a, "aaa");
// 	Path* first = CreatePath(a, 4);
// 	printf("%d %s", first->depth, first->name);
// 	DestroyPath(first);
// }
