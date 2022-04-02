#include "directory.h"

#define FTW_F 1 // файл, не являющийся каталогом
#define FTW_D 2 // каталог
#define FTW_DNR 3 // каталог, недоступный для чтения
#define FTW_NS 4 // файл, информацию о котором нельзя получить с помощью stat

#define LINK_T 0
#define DIR_T 1
#define FILE_T 2


int printer(const char *pathname, int depth, int file_type, FILE *out_file, const char *title)
{ 
	//printf(depth);
	if (depth == 0)	
		fprintf(out_file, "\n                                %s\n", title);
	else
	{
		for (int i = 0; i < depth; ++i)
			fprintf(out_file, "\t");
		fprintf(out_file, "|--");
	}


	char buf[100];
	if (file_type == FILE_T)
	{
		fprintf(out_file, "%s\n", pathname);
		return 0;
	}
	if (file_type == DIR_T)
	{
		fprintf(out_file, "%s/\n", pathname);
		return 0;
	}	
	
	if (file_type == LINK_T)
	{
		fprintf(out_file,  "%s/ is symbol link to file ", pathname);
		int bytes_read = readlink(pathname, buf, 100);
		buf[bytes_read] = '\0';
		fprintf(out_file, "%s\n", buf);
	}
	return 0;
}


// Обход дерева каталогов
int dopath(const char *filename, int depth, int print_fun(const char *, int, int, FILE *, const char *), const char *title, FILE *out_file, int max_depth)
{
	if (depth > max_depth)
		return 0;
	struct stat statbuf;
	struct dirent * dirp;
	DIR *dp;
	int ret = 0;

	if ((ret = lstat(filename, &statbuf)) != 0) // ошибка 																		
		return ret; 


	if (S_ISDIR(statbuf.st_mode) == 0) // не каталог 
	{
		if (S_ISLNK(statbuf.st_mode) == 0)// не симв. ссылка
			return(print_fun(filename, depth, FILE_T, out_file, title)); 
		return(print_fun(filename, depth, LINK_T, out_file, title));  
	}
	print_fun(filename, depth, DIR_T, out_file, title);//каталог отобразить в дереве 


	if ((dp = opendir(filename)) == NULL) // каталог недоступен

		return 0;
    
	chdir(filename); //меняет текущий рабочий каталог процесса. Без этого пришлось бы приписывать в цикле к dirp->d_name сзади filename ?? тк в dirp->d_name только имя файла без пути
	while ((dirp = readdir(dp)) != NULL && ret == 0)
	{
		if (strcmp(dirp->d_name, ".") != 0 &&
			strcmp(dirp->d_name, "..") != 0 ) // пропуск каталогов . и .. попали в текущую родительску директорию
		{
			ret = dopath(dirp->d_name, depth + 1, print_fun, title, out_file, max_depth);
		}
	}
    
	chdir("..");

	if (closedir(dp) < 0)
		perror("Невозможно закрыть каталог");

	return(ret);    
}

int read_directory(const char *dirname, FILE *out_file, int max_depth)
{
	return dopath(dirname, 0, printer, dirname, out_file, max_depth);
}
