// !!! with flag: -lpthread

#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

#define FILE_NAME "task3_pthread.txt"
#define ERROR_THREAD_CREATE -1
#define OK 0

void Info()
{
	struct stat statbuf;

	stat(FILE_NAME, &statbuf);
	printf("inode: %ld\n", statbuf.st_ino);
	printf("Общий размер в байтах: %ld\n", statbuf.st_size);
	printf("Размер блока ввода-вывода: %ld\n\n", statbuf.st_blksize);
}

void WriteToFile(char c)
{
	FILE *f = fopen(FILE_NAME, "w");
	Info();

	while (c <= 'z')
	{
		fprintf(f, "%c", c);
		c += 2;
	}

	fclose(f);
	Info();
}

void *thr_fn(void *arg)
{
	WriteToFile('b');
}

int main()
{
	pthread_t tid;

	int err = pthread_create(&tid, NULL, thr_fn, NULL);
	if (err)
	{
		printf("не­воз­мож­но соз­дать по­ток");
		return ERROR_THREAD_CREATE;
	}

	sleep(1);
	WriteToFile('a');
	pthread_join(tid, NULL);

	return OK;
}
