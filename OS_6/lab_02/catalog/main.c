// https://www.firststeps.ru/linux/r.php?20

#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "catalog.h"
#include "errors.h"
#include "constants.h"

// TODO: Создать все 7 видов файлов для наглядности.

int main(int argc, char *argv[])
{
	if (argc != COUNT_ARGS)
		err_sys("Укажите в аргументах командной строки один начальный каталог.");
	catalog(argv[DIR_NAME]);

	printf("\n\nOk!\n");
	return 0;
}