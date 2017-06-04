#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#define len 16

int main(int argc, char **argv)
{
	int fd_src, fd_tgt;
	int w;
	char buf[len];
	if (argc != 3)
	{
		printf("wrong arguments\n");
		exit(0);
	}
	if ((fd_src=open(argv[1], O_RDONLY, S_IRUSR)) == -1)
	{
		printf("Open %s Error: %s\n\a", argv[1], strerror(errno));
		exit(1);
	}
	if ((fd_tgt=open(argv[2],O_WRONLY|O_CREAT, S_IWUSR)) == -1) 
	{
		printf("Open %s Error: %s\n\a", argv[2], strerror(errno));
		exit(1);
	}
	while ((w=read(fd_src, buf, len))>0)
	{
		if((write(fd_tgt, buf, len))<0)
			break;
	}	
	close(fd_src);
	close(fd_tgt);
	return 0;
}
