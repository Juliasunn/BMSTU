#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#include "path.h"
#include "stack.h"
#include "errors.h"
#include "constants.h"

void output_dir(DIR *dir)
{
	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
	{
			// Пропускаем ка­та­ло­ги "." и ".."
		if (strcmp(entry->d_name, ".") != 0 &&
			strcmp(entry->d_name, "..") != 0)
		{

			ExpandPath(curr_path, entry->d_name, curr_len);

			OutputPath(entry->d_name, curr_path->depth, '_');

			if (lstat(curr_path->name, &statbuf) == ERROR_LSTAT)
				error_lstat();

				// Если каталог, то добавляем в стек.
			if (S_ISDIR(statbuf.st_mode))
				output_dir(DIR *dir)
				//Push(stack, curr_path->name, curr_path->depth + 1);

		}
	}
}

void catalog(char *pathname)
{
	Stack *stack = CreateStack();
	Path *curr_path;
	int curr_len;

	DIR *dir;
	struct dirent *entry;
	struct stat statbuf;

	// Записываем в statbuf информацию о файле.
	if (lstat(pathname, &statbuf) == ERROR_LSTAT)
		error_lstat();

	if (!S_ISDIR(statbuf.st_mode))
		err_sys("Введенный путь не является каталогом.");

	Push(stack, pathname, 1);

	while (stack->count)
	{
		curr_path = Pop(stack);

		dir = opendir(curr_path->name);
		if (!dir)
			err_sys("Ошибка diropen");

		curr_len = strlen(curr_path->name);
		
		
		while ((entry = readdir(dir)) != NULL)
		{
			// Пропускаем ка­та­ло­ги "." и ".."
			if (strcmp(entry->d_name, ".") != 0 &&
				strcmp(entry->d_name, "..") != 0)
			{

				// Расширяем текущий путь.
				// Т.е. добавляем в конец имя текущего файла.
				ExpandPath(curr_path, entry->d_name, curr_len);

				// printf("%s\n", curr_path->name);
				OutputPath(entry->d_name, curr_path->depth, '_');

				if (lstat(curr_path->name, &statbuf) == ERROR_LSTAT)
					error_lstat();

				// Если каталог, то добавляем в стек.
				if (S_ISDIR(statbuf.st_mode))
					Push(stack, curr_path->name, curr_path->depth + 1);

				// printf("Catalog = %d\n", S_ISDIR());
				// printf("%ld - %s [%d] %d\n\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
			}
		}

		if (closedir(dir) < 0)
			exit(1);
	}

	DestroyStack(stack);
}
