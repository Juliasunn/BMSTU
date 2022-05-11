#include <stdio.h>
#include <sys/stat.h>

#define FILE_NAME "task3.txt"
#define OK 0

void Info()
{
	struct stat statbuf;

	stat(FILE_NAME, &statbuf);
	printf("inode: %ld\n", statbuf.st_ino);
	printf("Общий размер в байтах: %ld\n", statbuf.st_size);
	printf("Размер блока ввода-вывода: %ld\n\n", statbuf.st_blksize);
}

int main()
{

	FILE *f1 = fopen(FILE_NAME, "w");
	Info();

	FILE *f2 = fopen(FILE_NAME, "w");
	Info();

	char c = 'a'; // 97
	while (c <= 'z')
	{
		if (c % 2)
		{
			fprintf(f1, "%c", c); // acej...
		}
		else
		{
			fprintf(f2, "%c", c); // bdfh...
		}
		c++;
	}

	fclose(f1);
	Info();

	fclose(f2);
	Info();

	return OK;
}