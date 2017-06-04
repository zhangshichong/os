#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, r, p1, p2, fd[2];
	char buf[50], s[50];
	pipe(fd);
	while ((p1=fork())==-1);
	if (p1 == 0)
	{
		lockf(fd[1], 1, 0);
		sprintf(buf, "message from child process1 \n");
		printf("child process 1\n");
		write(fd[1], buf, 50);
		sleep(5);
		lockf(fd[1], 0, 0);
		exit(0);
	}
	else
	{
		while((p2=fork())==-1);
		if(p2 == 0)
		{
			lockf(fd[1], 1, 0);
			sprintf(buf, "message from child process2 \n");
			printf("child process2\n");
			write(fd[1], buf, 50);
			sleep(5);
			lockf(fd[1], 0, 0);
			exit(0);
		}
		wait(0);
		if ( r=read(fd[0], s, 50) == -1)
			printf("cannot read pipe1\n");
		else printf("%s\n", s);
		wait(0);
		if (r=read(fd[0], s, 50) == -1)
			printf("cannot read pipe2\n");
		else printf("%s\n", s);
		exit(0);
	}
	return 0;
}
