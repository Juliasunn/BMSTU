#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

void err_sys(const char *x)
{
	perror(x);
	exit(1);
}

void error_lstat()
{
	switch (errno)
	{
	case EBADF:
		err_sys("Неверный файловый описатель filedes.");
		break;
	case ENOENT:
		err_sys("Компонент полного имени файла file_name не существует или полное имя является пустой строкой.");
		break;
	case ENOTDIR:
		err_sys("Компонент пути не является каталогом.");
		break;
	case ELOOP:
		err_sys("При поиске файла встретилось слишком много символьных ссылок.");
		break;
	case EFAULT:
		err_sys("Некорректный адрес.");
		break;
	case EACCES:
		err_sys("Запрещен доступ.");
		break;
	case ENOMEM:
		err_sys("Недостаточно памяти в системе.");
		break;
	case ENAMETOOLONG:
		err_sys("Слишком длинное название файла.");
		break;

	default:
		err_sys("Ошибка lstat.");
		break;
	}
}