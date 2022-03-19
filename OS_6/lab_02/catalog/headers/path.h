#ifndef _PATH_H_

#define _PATH_H_

typedef struct
{
	char *name;
	int depth;
} Path;

Path *CreatePath(char *name, int depth);

void DestroyPath(Path *path);

void ExpandPath(Path *path, char *filename, int curr_len);

void OutputPath(char *name, int depth, char const symbol);

#endif
