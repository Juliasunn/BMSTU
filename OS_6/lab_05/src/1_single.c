//gcc -c 1_single.c
//gcc -o 1_single.exe 1_single.o

#include <stdio.h>
#include <fcntl.h>

#define OK 0
#define FILE_NAME "alphabet.txt"
#define BUFF_SIZE 20

#define GREEN "\33[32m"
#define BLUE "\33[34m"
#define RED "\33[31m"

int main()
{
	int fd = open(FILE_NAME, O_RDONLY); // O_RDONLY - только на чтение.

	FILE *fs1 = fdopen(fd, "r");
	char buff1[BUFF_SIZE];
	setvbuf(fs1, buff1, _IOFBF, BUFF_SIZE); // _IOFBF - блочная буферизация.

	FILE *fs2 = fdopen(fd, "r");
	char buff2[BUFF_SIZE];
	setvbuf(fs2, buff2, _IOFBF, BUFF_SIZE);

	int flag1 = 1, flag2 = 2;

	// printf("\nTEST: %s\n", fs1->_IO_read_ptr);
	// printf("\nBOOL: %d\n", fs1->_IO_read_end == fs1->_IO_read_ptr);

	while (flag1 == 1 || flag2 == 1)
	{
		char c;
		flag1 = fscanf(fs1, "%c", &c);
		if (flag1 == 1)
		{
			fprintf(stdout, GREEN "%c", c);
		}
		flag2 = fscanf(fs2, "%c", &c);
		if (flag2 == 1)
		{
			fprintf(stdout, BLUE "%c", c);
		}
	}

	printf("\n");
	return OK;
}
