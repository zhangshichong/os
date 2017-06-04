#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define Length 1024

int main()
{
	int fdw, fdr, len;
	char str[Length];
	char sourcename[20];
	char targetname[20];
	printf("Please input source file\n");
	gets(sourcename);
	printf("Please input target file\n");
	gets(targetname);
	fdr = open(sourcename, O_RDONLY);
	if(fdr) len = read(fdr, str, Length);
	else 
	{
		printf("read file error\n");
		exit(0);
	}
	fdw = open(targetname, O_CREAT|O_RDWR);
	write(fdw, str, len);
	close(fdr);
	close(fdw);
}
