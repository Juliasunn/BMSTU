//gcc -c 1_multi.c -pthread
//gcc -o 1_multi.exe 1_multi.o -lpthread
#include <unistd.h> //for sleep function

#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>


#define OK 0
#define FILE_NAME "alphabet.txt"
#define BUFF_SIZE 20
#define ERROR_THREAD_CREATE -1


#define GREEN "\33[32m"
#define BLUE "\33[34m"
#define RED "\33[31m"

int fd;

void *thread_fn(void *arg)
{
	FILE *fs2 = fdopen(fd, "r");
	char buff2[BUFF_SIZE];
	setvbuf(fs2, buff2, _IOFBF, BUFF_SIZE);
	
	char c;
	while (fscanf(fs2, "%c", &c)==1)
	{
		fprintf(stdout, GREEN "%c", c);
		sleep(0.5);	
	}
}

int main()
{
	pthread_t tid;
	                         
	fd = open(FILE_NAME, O_RDONLY); // O_RDONLY - только на чтение.
	
	int err = pthread_create(&tid, NULL, thread_fn, 0);
	if (err)
	{
		printf("не­воз­мож­но соз­дать по­ток");
		return ERROR_THREAD_CREATE;
	}

	FILE *fs1 = fdopen(fd, "r");
	char buff1[BUFF_SIZE];
	setvbuf(fs1, buff1, _IOFBF, BUFF_SIZE); // _IOFBF - блочная буферизация.
	
	char c;
	while (fscanf(fs1, "%c", &c)==1)
	{
		fprintf(stdout, BLUE "%c", c);
		sleep(0.5); //чтобы функция во 2-м потоке успела выполнить fscanf и заполнить буфер 6 оставшимися символами	
	}
	
	pthread_join(tid, NULL);
	printf("\n");
	return OK;
}
