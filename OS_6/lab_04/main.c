
//gcc -c main.c
//gcc -o app.exe main.o
#include "directory.h"
#include "special_print.h"
#include <unistd.h> //for readlink func
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH_LENGTH 256
#define BUF_SIZE 3000

int simple_print(const char *buf, FILE *out_file, const char *title)
{
	fprintf(out_file, "\n                                %s\n", title);
	fprintf(out_file, "%s\n", buf);
}

int read_symblink(const char *process_dir, const char *link_name, FILE *out_file, int print_func(const char *, FILE *, const char *))
{
	char path[MAX_PATH_LENGTH];
	snprintf(path, MAX_PATH_LENGTH, "%s%s", process_dir, link_name);
	char buf[BUF_SIZE];
	int len;
	printf("[DEBUG INFO: file name] %s\n", path);
	if ( (len = readlink(path, buf, BUF_SIZE)) < 0)
		return -1;
		  
	buf[len] = 0; 
	print_func(buf, out_file, path);
}


int read_dir(const char *process_dir, const char *dir_name, FILE *out_file)
{
	char path[MAX_PATH_LENGTH];
	snprintf(path, MAX_PATH_LENGTH, "%s%s", process_dir, dir_name);


	printf("[DEBUG INFO: file name] %s\n", path);

	read_directory(path, out_file);	  
}


int read_proc_file(const char *process_dir, const char *file_name, FILE *out_file, int print_func(const char *, FILE *, const char *))
{
	char path[MAX_PATH_LENGTH];
	snprintf(path, MAX_PATH_LENGTH, "%s%s", process_dir, file_name);
	
	FILE *proc_file = fopen(path, "r");
	if (!proc_file)
		return -1;

	char buf[BUF_SIZE];
	int len;
	
	printf("[DEBUG INFO: file name] %s\n", path);

	// Возвращает кол-во действительно прочитанных объектов.
	while ((len = fread(buf, 1, BUF_SIZE, proc_file)) > 0)
	{	
		for (int i = 0; i < len; i++)
			if (buf[i] == 0)
				buf[i] = 10; 	// EOF
		buf[len] = 0; 			// '\0'
		print_func(buf, out_file, path);
	}

	fclose(proc_file);
}


int main(int argc, char *argv[])
{
	char process_dir[MAX_PATH_LENGTH] = "/proc/";
	if (argc != 2)
		strcat(process_dir, "self"); //Файл /proc/self является символической ссылкой на каталог, соответствующий текущему процессу.
        else
        	strcat(process_dir, argv[1]); //иначе PID процесса передается как параметр 
        FILE *out_file = fopen("process_info.txt", "w"); //текстовый файл куда выводим информацию о процессе
        
        read_proc_file(process_dir, "/cmdline", out_file, simple_print);
        read_symblink(process_dir, "/cwd", out_file, simple_print);
        read_symblink(process_dir, "/exe",  out_file, simple_print);      
        read_symblink(process_dir, "/root", out_file, simple_print);
        
        read_dir(process_dir, "/fd", out_file);
        read_proc_file(process_dir, "/stat",  out_file, stat_print);
        read_proc_file(process_dir, "/environ", out_file, simple_print);

        
        fclose(out_file);
        return 0;
}
