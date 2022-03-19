#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>	  
#include <sys/stat.h> 
#include <unistd.h>
#include <pthread.h>
#include <time.h> 

#include <sys/time.h>
#include <sys/resource.h>

#define LOCKFILE "/var/run/my_daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

sigset_t mask;


int lockfile(int fd)
{

	struct flock fl;

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
		syslog(LOG_ERR, "невозможно открыть %s: %s", LOCKFILE, strerror(errno));
		exit(1);
	}
	if (lockfile(fd) < 0)
	{
		if (errno == EACCES || errno == EAGAIN)
		{
			close(fd);
			return (1);
		}
		syslog(LOG_ERR, "невозможно установить блокировку на %s: %s", LOCKFILE, strerror(errno));
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
	umask(0); // user mask

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: невозможно получить максимальный номер дескриптора ", cmd);

	if ((pid = fork()) < 0)
		err_quit("%s: ошибка вызова функции fork", cmd);
	else if (pid != 0) 
		exit(0);	   /
	
	pid_t new_session_id = setsid();
	syslog(LOG_WARNING, "ID новой сессии  %d ID процесса: %d", new_session_id, getpid());
	sa.sa_handler = SIG_IGN;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: невозможно игнорировать сигнал SIGHUP", cmd);


	if (chdir("/") < 0)
		err_quit("%s: невозможно сделать текущим рабочим каталогом /", cmd);

	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (int i = 0; i < rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR, "ошибочные файловые дескрипторы %d %d %d",
			   fd0, fd1, fd2);
		exit(1);
	}
}

void *thr_fn(void *arg)
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
			syslog(LOG_INFO, "Получен сигнал SIGHUP getlogin = %s", getlogin());
			break;
		case SIGTERM:
			syslog(LOG_INFO, "Получен сигнал SIGTERM; вы­ход");

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


	daemonize("my_daemon");
	if (already_running() != 0)
	{
		syslog(LOG_ERR, "Демон уже запущен!\n");
		exit(1);
	}


	sa.sa_handler = SIG_DFL; //
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: не­воз­мож­но вос­ста­но­вить дей­ст­вие SIG_DFL для SIGHUP");
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		err_exit(err, "ошиб­ка вы­пол­не­ния опе­ра­ции SIG_BLOCK");

	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
		err_exit(err, "не­воз­мож­но соз­дать по­ток");

	syslog(LOG_WARNING, "Проверка пройдена!");

	long int ttime;
	
	while (1)
	{
		ttime = time(NULL);
		syslog(LOG_INFO, "Демон! Время: %s", ctime(&ttime));
		sleep(3);
	}
}
