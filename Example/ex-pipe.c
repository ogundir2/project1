/************  ex-pipe.c ************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	string1[] = "Hello, this is the parent process";
char	string2[] = "Hi, this is the child process";

int main()
{
	char	buf[1024];
	int	i, fds1[2], fds2[2];

	if (pipe(fds1) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(fds2) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (fork()>0)
	{
		for (i=0; i<3; i++) {
			write(fds1[1], string1, sizeof(string1));
			read(fds2[0],buf,sizeof(string2));
			printf("parent read %s\n", buf);
		}
		exit(0);
	}
	else
	{
		for (i=0; i<3; i++) {
			write(fds2[1], string2, sizeof(string2));
			read(fds1[0], buf, sizeof(string1));
			printf("child read %s\n", buf);
		}
	}
}
