#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <queue>
#include <string>
#define Length 1024 //added
using namespace std;

int main(int argc, char **argv)
{
	DIR *dirp;
	struct dirent *direntp;
	int stats;
	char path[1024];
	queue<string> dir_file;
	dir_file.push(argv[1]);
	if(argc != 2)
	{
		printf("Usage:%s filename\n\a", argv[0]);
		exit(1);
	}
   while(!dir_file.empty())
 {
	if((dirp=opendir(dir_file.front().c_str()))==NULL)
	{
		printf("Open Directory %s Error: %s\n", argv[1], strerror(errno));
		exit(0);
	}
	while((direntp = readdir(dirp)) != NULL)
	{
	struct stat statbuf;
	string s_path;
	s_path = dir_file.front();
	s_path += "/";
	s_path += direntp->d_name;
	if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
		continue;
	if(stat(s_path.c_str(), &statbuf) == -1)
	{
		printf("Get stat on %s Error: %s\n", path, strerror(errno));
		return -1;
	}
	if(S_ISDIR(statbuf.st_mode))
	{
       		dir_file.push(s_path);
	}
	if(S_ISREG(statbuf.st_mode))
	{
         	printf("%ssize:%ldbytes\tmodifiedat%s", s_path.c_str(),statbuf.st_size,ctime(&statbuf.st_mtime));
	} 
	}
	closedir(dirp);
        dir_file.pop();
}
	return 0;
}
