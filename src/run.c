#include "cscript.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int run(char *path, char **argv)
{
	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork error\n");
		exit(pid);
	}
	if (pid == 0)
		return execvp(path, argv);

	int statval;
	wait(&statval);
	if (WIFEXITED(statval))
		return WEXITSTATUS(statval);
	return -1;	
}
