//gcc -c 2_multi.c -pthread
//gcc -o 2_multi.exe 2_multi.o -lpthread
#include <fcntl.h>
#include <unistd.h> // read, write.
#include <pthread.h>
#include <stdio.h>

#define OK 0
#define ERROR_THREAD_CREATE -1
#define FILE_NAME "alphabet.txt"

void read_file(int fd)
{
	char c;
	while (read(fd, &c, 1))
	{
		write(1, &c, 1);
	}
}

void *thr_fn(void *arg)
{
	int fd = open(FILE_NAME, O_RDONLY);
	read_file(fd);
}

int main()
{
	pthread_t tid;

	int fd = open(FILE_NAME, O_RDONLY);

	// NULL - атрибуты по умолчанию
	// arg = 0 не передаем аргументы.
	int err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err)
	{
		printf("не­воз­мож­но соз­дать по­ток");
		return ERROR_THREAD_CREATE;
	}

	read_file(fd);
	pthread_join(tid, NULL);
	printf("\n");
	return OK;
}
