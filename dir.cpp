#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <queue>
using namespace std;

int main(int argc, char **argv)
{
	queue<char [256]> q_path;
	DIR *dirp;
	struct dirent *direntp;
	char path[256];
	if ((dirp = opendir(argv[1])) == NULL)
	{
		printf("Open Directort %s Error: %s\n", argv[1], strerror(errno));
		exit(1);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		struct stat statbuf;
		memset(path, 0, 256);
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, direntp->d_name);
		if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
			continue;
		if ((stat(path, &statbuf)) == -1)
		{
			printf("Get stat on %s Error: %s\n", path, strerror(errno));
			exit(1);
		}
		if (S_ISREG(statbuf.st_mode))
			printf("%s size: %ld bytes \t modified at %s", path, statbuf.st_size, ctime(&statbuf.st_mtime));
		if (S_ISDIR(statbuf.st_mode))
		{
			printf("%s is a directory\n", path);
		}
	}
	return 0;
}


