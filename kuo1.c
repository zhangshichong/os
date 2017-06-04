#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define len 16
static int get_file_size_time(const char* filename)
{
	struct stat statbuf;
	if(stat(filename, &statbuf) == -1)
	{
		printf("Get stat on %s Error: %s\n", filename, strerror(errno));
		return -1;
	}
	if(S_ISDIR(statbuf.st_mode))
		return 1;
	if(S_ISREG(statbuf.st_mode))
		printf("%s size: %ld bytes \tmodified at %s", filename, statbuf.st_size, ctime(&statbuf.st_mtime));
	return 0;
}
void copy(char *src, char *tgt)
{
	int fd_src, fd_tgt;
	int w;
	char buf[len];
	if ((fd_src = open(src, O_RDONLY, S_IRUSR)) == -1)
	{
		printf("Open %s Error: %s\n\a", src, strerror(errno));
		exit(1);
	}
	if ((fd_tgt = open(tgt, O_WRONLY|O_CREAT, S_IWUSR)) == -1)
	{
		printf("Open %s Error: %s\n\a", tgt, strerror(errno));
		exit(1);
	}
	while (( w=read(fd_src, buf, len)) > 0)
	{
		if ((write(fd_tgt, buf, w)) < 0)
			break;
	}
	close(fd_src);
	close(fd_tgt);
}
int main(int argc, char **argv)
{
	int src = 0;
	char *src_name = "source.txt";
	char *tgt_name = "target.txt";
	DIR *dirp;
	struct dirent *direntp;
	int stats;
	char path[1024];
	char t_path[1024];
	memset(t_path, 0, 1024);
	if(argc != 2)
	{
		printf("Usage:%s filename\n\a", argv[0]);
		exit(1);
	}
	if(((stats=get_file_size_time(argv[1])) == 0) || (stats == -1))
		exit(1);
	if((dirp=opendir(argv[1]))==NULL)
	{
		printf("Open Directory %s Error: %s\n", argv[1], strerror(errno));
		exit(0);
	}
	while((direntp = readdir(dirp)) != NULL)
	{
		memset(path, 0, 1024);
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcpy(t_path, path);
		strcat(t_path, tgt_name);
		strcat(path, direntp->d_name);
		if ((strcmp(direntp->d_name, src_name) == 0) && (src == 0))
		{
			src = 1;
			copy(path, t_path);
		}
		if(get_file_size_time(path) == -1)
			break;
	}
	closedir(dirp);
	exit(1);
	return 0;
}
