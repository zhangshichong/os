#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void init_daemon()
{
	int pid;
	int i;
	if (pid = fork()) exit(0);
	else if (pid < 0) exit(1);
	setsid();
	if (pid = fork()) exit(0);
	else if (pid < 0) exit(1);
	for (i=0; i<NOFILE; ++i)
		close(i);
	chdir("~/os");
	umask(0);
	return;
}
int main()
{
	FILE *fp;
	time_t t;
	init_daemon;
	while(1)
	{
		sleep(10);
		if ((fp=fopen("daemon.log", "a")) >= 0)
		{
			time(&t);
			fprintf(fp, "log time : %s ",asctime(localtime(&t)));
			fclose(fp);
		}
	}
	return 0;
}
