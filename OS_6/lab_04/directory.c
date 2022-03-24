#include "directory.h"

#define FTW_F 1 // файл, не являющийся каталогом
#define FTW_D 2 // каталог
#define FTW_DNR 3 // каталог, недоступный для чтения
#define FTW_NS 4 // файл, информацию о котором нельзя получить с помощью stat



int printer(const char *pathname, FILE *f, const char *title)
{ 
	char buf[100];
	printf( "-- %s/ ", pathname);
	readlink(pathname, buf, 100);
	printf("%s/\n", buf);
	return 0;
}


// Обход дерева каталогов
int dopath(const char *filename, int depth, const char *title, int func(const char *, FILE *, const char *))
{
	struct stat statbuf;
	struct dirent * dirp;
	DIR *dp;
	int ret = 0;

	if ((ret = lstat(filename, &statbuf)) != 0) // ошибка 																		
		return ret; 

	for (int i = 0; i < depth; ++i)
		printf("|\t");

	if (S_ISDIR(statbuf.st_mode) == 0) // не каталог 
		return(func(filename, &statbuf, FTW_F)); // отобразить в дереве 

	if ((ret = func(filename, &statbuf, FTW_D)) != 0)
		return(ret);

	if ((dp = opendir(filename)) == NULL) // каталог недоступен
		return(func(filename, &statbuf, FTW_DNR));
    
	chdir(filename); //меняет текущий рабочий каталог процесса. Без этого пришлось бы приписывать в цикле к dirp->d_name сзади filename ?? тк в dirp->d_name только имя файла без пути
	while ((dirp = readdir(dp)) != NULL && ret == 0)
	{
		if (strcmp(dirp->d_name, ".") != 0 &&
			strcmp(dirp->d_name, "..") != 0 ) // пропуск каталогов . и .. попали в текущую родительску директорию
		{
			ret = dopath(dirp->d_name, depth + 1, func);
		}
	}
    
	chdir("..");

	if (closedir(dp) < 0)
		perror("Невозможно закрыть каталог");

	return(ret);    
}

int read_directory(const char *dirname)
{
	return dopath(dirname, 0, printer);
}
