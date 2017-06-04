#include <stdio.h>
#include <stdlib.h>
int main()
{
	int x, fd[2];
	char buf[30], s[30];
	pipe(fd);
	while ((x = fork()) ==-1);
	if (x == 0)
	{
		sprintf(buf,"This is an example\n");
		write(fd[1], buf, 30);
	}
	else
	{
		wait(0);
		read(fd[0], s, 30);
		printf("%s\n", s);
	}
	return 0;
}
