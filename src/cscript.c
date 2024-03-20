#include "cscript.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	srand(time(NULL));
	int status;
	int temp_cnt = 0;
	char *temp_filenames[4];

	char **target_argv = malloc((argc + 1) * sizeof(char *));
	int source_fd;
	
	status = parse_argv(argc, argv, 
	                    &source_fd, target_argv,
											&temp_cnt, temp_filenames);
	if (status < 0) {
		perror("Parse error\n");
		exit(status);
	}
	debug("parse_argv done\n");

	int code_fd;
	char *code_filename = mktmp(&code_fd);
	temp_filenames[temp_cnt++] = code_filename;
	debug("temp_filename <%s> created\n", code_filename);

	bool main_exist;
	status = read_code(source_fd, code_fd, &main_exist);
	close(source_fd);
	if (status < 0) {
		perror("Read file error\n");
		exit(status);
	}
	debug("read code done, main_exist: %d\n", main_exist);

	int processed_fd;
	char *processed_filename = mktmp(&processed_fd);
	temp_filenames[temp_cnt++] = processed_filename;
	status = preprocess_code(code_fd, processed_fd, main_exist);
	if (status < 0) {
		perror("Preprocess failed\n");
		exit(status);
	}
	debug("processed_filename <%s> created\n", processed_filename);

	char *target_filename = malloc(strlen(FILENAME_TEMPLATE) + 1);
	strcpy(target_filename, FILENAME_TEMPLATE);
	for (int i = strlen(FILENAME_TEMPLATE) - 1, j = 0; j < 6; i--, j++) {
		target_filename[i] = rand() % 52;
		if (target_filename[i] < 26)
			target_filename[i] += 'a';
		else
			target_filename[i] += -26 + 'A';
	}
	temp_filenames[temp_cnt++] = target_filename;
	target_argv[0] = target_filename;
	debug("target filename <%s> created\n", target_filename);

	status = compile(processed_fd, target_filename);
	close(code_fd);
	if (status < 0) {
		perror("Compile failed\n");
		exit(status);
	}
	debug("compile done\n");

	status = run(target_filename, target_argv);
	free(target_argv);
	if (status < 0) {
		perror("Run failed\n");
		exit(status);
	}

#ifndef DEBUG
	status = cleanup(temp_cnt, temp_filenames);
	if (status < 0) {
		perror("Cleanup failed\n");
		exit(status);
	}
#endif
	return 0;
}
