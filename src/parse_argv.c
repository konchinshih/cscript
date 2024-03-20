#include "cscript.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int parse_argv(int argc, char **argv, 
               int *source_fd, char **target_argv, 
               int *temp_cnt, char **temp_filenames)
{
	int target_argc = 1;
	*source_fd = -1;
	debug("0: %s\n", argv[0]);
	for (int i = 1; i < argc; i++) {
		debug("%d: %s\n", i, argv[i]);
		if (strlen(argv[i]) && argv[i][0] == '-') {
			if (strcmp(argv[i], "-") == 0) {
				*source_fd = STDIN_FILENO;
			} else if (strcmp(argv[i], "-c") == 0) {
				if (i + 1 >= argc)
					return -1;

				char *source_filename = malloc(sizeof(FILENAME_TEMPLATE));
				strcpy(source_filename, FILENAME_TEMPLATE);
				*source_fd = mkstemp(source_filename);
				temp_filenames[(*temp_cnt)++] = source_filename;
				if (*source_fd < 0)
					return -1;

				off_t start = lseek(*source_fd, (size_t)0, SEEK_CUR);
				debug("%d: %s\n", i + 1, argv[i + 1]);
				write(*source_fd, argv[i + 1], strlen(argv[i + 1]) + 1);
				lseek(*source_fd, start, SEEK_SET);

				i++;
			}
		} else if (*source_fd == -1) {
			*source_fd = open(argv[i], O_RDONLY);
			
			if (*source_fd < 0)
				return -1;
		} else {
			int arg_len = strlen(argv[i]);
			target_argv[target_argc] = malloc(arg_len * sizeof(char));
			memcpy(target_argv[target_argc], argv[i], arg_len);
			target_argc++;
		}
	}
	if (*source_fd == -1)
		*source_fd = STDIN_FILENO;
	debug("source_fd: %d\n", *source_fd);
	target_argv[target_argc] = (char *)0;
	return 0;
}
