// Переход в корень диска, необходим для того, чтобы
// впоследствии не было проблем связанных с размонтированием дисков.
// Если текущая папка демона будет находиться на диске,
// который необходимо будет отмонтировать, то система не даст этого,
// до тех пор, пока демон не будет остановлен.

#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

#include <pthread.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

sigset_t mask;

void reader(void)
{
	//
}

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// Установка блокировки для записи на весь файл
int lockfile(int fd)
{
	struct flock
	{
		short l_type;
		short l_whence;
		off_t l_start;
		off_t l_len;
		pid_t l_pid;
	} fl;

	// struct flock fl;
	fl.l_type = F_WRLCK;

	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return (fcntl(fd, F_SETLK, &fl));
}

int already_running(void)
{
	int fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
	if (fd < 0)
	{
		syslog(LOG_ERR, "невозможно открыть %s: %s",
			   LOCKFILE, strerror(errno));
		exit(1);
	}
	if (lockfile(fd) < 0)
	{
		if (errno == EACCES || errno == EAGAIN)
		{
			close(fd);
			return (1);
		}
		syslog(LOG_ERR, "невозможно установить блокировку на %s: %s",
			   LOCKFILE, strerror(errno));
		exit(1);
	}
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);
	return (0);
}

void daemonize(const char *cmd)
{

	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	/*
         * Сбросить маску режима создания файла.
         */
	umask(0);
	/*
         * Получить максимально возможный номер дескриптора файла.
         */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		exit(2);
		// err_quit("%s: невозможно получить максимальный номер дескриптора ", cmd);
	}

	/*
         * Стать лидером нового сеанса, чтобы утратить управляющий терминал.
         */
	if ((pid = fork()) < 0)
	{
		// err_quit("%s: ошибка вызова функции fork", cmd);
		exit(1);
	}
	else if (pid != 0) /* родительский процесс */
		exit(0);

	setsid();

	/*
         * Обеспечить невозможность обретения управляющего терминала в будущем.
         */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
	{
		// err_quit("%s: невозможно игнорировать сигнал SIGHUP", cmd);
		exit(3);
	}
	if ((pid = fork()) < 0)
	{
		// err_quit("%s: ошибка вызова функции fork", cmd);
		exit(4);
	}
	else if (pid != 0) /* родительский процесс */
		exit(0);

	FILE *fp = fopen("log.txt", "a");

	fprintf(fp, "Стадия 1\n");

	/*
         * Назначить корневой каталог текущим рабочим каталогом,
         * чтобы впоследствии можно было отмонтировать файловую систему.
         */
	if (chdir("/") < 0)
	{
		// err_quit("%s: невозможно сделать текущим рабочим каталогом /", cmd);
		exit(5);
	}

	fprintf(fp, "Стадия 2\n");
	fclose(fp);

	/*
         * Закрыть все открытые файловые дескрипторы.
         */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/*
         * Присоединить файловые дескрипторы 0, 1 и 2 к /dev/null.
         */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	fp = fopen("log.txt", "a");

	fprintf(fp, "Стадия 3\n");

	fclose(fp);
	/*
         * Инициализировать файл журнала.
         */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "ошибочные файловые дескрипторы %d %d %d",
			   fd0, fd1, fd2);
		exit(1);
	}
}

void *
thr_fn(void *arg)
{
	int err, signo;
	for (;;)
	{
		err = sigwait(&mask, &signo);
		if (err != 0)
		{
			syslog(LOG_ERR, "ошиб­ка вы­зо­ва функ­ции sigwait");
			exit(1);
		}
		switch (signo)
		{
		case SIGHUP:
			syslog(LOG_INFO, "Чте­ние кон­фи­гу­ра­ци­он­но­го фай­ла");
			reread();
			break;
		case SIGTERM:
			syslog(LOG_INFO, "по­лу­чен сиг­нал SIGTERM; вы­ход");

			exit(0);
		default:
			syslog(LOG_INFO, "по­лу­чен не­пред­ви­ден­ный сиг­нал %d\n", signo);
		}
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int err;
	pthread_t tid;
	char *cmd;
	struct sigaction sa;
	if ((cmd = strrchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;
	/*
	* Пе­рей­ти в ре­жим де­мо­на.
	*/
	daemonize(cmd);
	/*
	* Убе­дить­ся, что ра­нее не бы­ла за­пу­ще­на дру­гая ко­пия де­мо­на.
	*/
	if (already_running())
	{
		syslog(LOG_ERR, "де­мон уже за­пу­щен");
		exit(1);
	}
	/*
	* Вос­ста­но­вить дей­ст­вие по умол­ча­нию для сиг­на­ла SIGHUP
	* и за­бло­ки­ро­вать все сиг­на­лы.
	*/
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: не­воз­мож­но вос­ста­но­вить дей­ст­вие SIG_DFL для SIGHUP");
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		err_exit(err, "ошиб­ка вы­пол­не­ния опе­ра­ции SIG_BLOCK");
	/*
	* Соз­дать по­ток для об­ра­бот­ки SIGHUP и SIGTERM.
	*/
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
		err_exit(err, "не­воз­мож­но соз­дать по­ток");

	/*
	* Ос­таль­ная часть про­грам­мы-де­мо­на.
	*/
	/* ... */
	exit(0);
}