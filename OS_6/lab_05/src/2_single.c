//testKernelIO.c
#include <fcntl.h>
#include <unistd.h> // read, write.

#define OK 0
#define FILE_NAME "alphabet.txt"

int main()
{
	char c;

	int fd1 = open(FILE_NAME, O_RDONLY);
	int fd2 = open(FILE_NAME, O_RDONLY);

	while (read(fd1, &c, 1) && read(fd2, &c, 1))
	{
		write(1, &c, 1);
		write(1, &c, 1);
	}

	write(1, "\n", 1);
	return OK;
}
