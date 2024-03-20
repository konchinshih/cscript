#include "cscript.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int compile(int code_fd, char *target_filename)
{
	pid_t pid = fork();
	if (pid < 0) {
		perror("Fork error\n");
		return pid;
	}
	if (pid == 0) {
		dup2(code_fd, 0);
		return execl(CXX_PATH, CXX, "-xc", "-", "-o", target_filename, (char *)0);
	}
	int statval;
	wait(&statval);
	return WEXITSTATUS(statval);
}
