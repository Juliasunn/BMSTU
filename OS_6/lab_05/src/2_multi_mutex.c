//gcc -c 2_multi_mutex.c -pthread
//gcc -o 2_multi_mutex.exe 2_multi_mutex.o -lpthread
#include <unistd.h> //for sleep function
#include <fcntl.h>
#include <unistd.h> // read, write.
#include <pthread.h>
#include <stdio.h>

#define OK 0
#define ERROR_THREAD_CREATE -1
#define FILE_NAME "alphabet.txt"

pthread_mutex_t lock;

void read_file(int fd)
{
	char c;
	pthread_mutex_lock(&lock);
	while (read(fd, &c, 1))
	{
		write(1, &c, 1);
	}
	pthread_mutex_unlock(&lock);
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
