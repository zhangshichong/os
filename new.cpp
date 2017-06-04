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
#include <vector>
#include <string>
#include <iterator>	
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	vector<string> q_path;
	DIR *dirp;
	struct dirent *direntp;
	q_path.push_back(argv[1]);
	while (!q_path.empty())
	{
		if ((dirp = opendir(q_path.front().c_str())) == NULL)
		{
			printf("Open Directory %s Error: %s\n", q_path.front().c_str(), strerror(errno));
			exit(1);
		}
		while ((direntp = readdir(dirp)) != NULL)
		{
			struct stat statbuf;
			string path;
			path = q_path.front();
			path += "/";
			path += direntp->d_name;
			//char path[256];
			//memset(path, 0, 256);
			//strcpy(path, q_path.front());
			//strcat(path, "/");
			//strcat(path, direntp->d_name);

			if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
				continue;
			if ((stat(path.c_str(), &statbuf)) == -1)
			{
				printf("Get stat on %s Error: %s\n", path.c_str(), strerror(errno));
				exit(1);
			}
			if (S_ISREG(statbuf.st_mode))
				printf("%s size: %ld bytes \t modified at %s", path.c_str(), statbuf.st_size, ctime(&statbuf.st_mtime));
			if (S_ISDIR(statbuf.st_mode))
			{
				q_path.push_back(path);
			}
		}
		closedir(dirp);
		q_path.erase(q_path.begin());
	}
	return 0;
}
