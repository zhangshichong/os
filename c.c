#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	char command[32];
	char *prompt = "$";
	while (printf("%s", prompt), gets(command) != NULL)
	{
		if (fork() == 0)
			execlp(command, command, NULL);
		else
			wait(0);
	}
	return 0;
}
