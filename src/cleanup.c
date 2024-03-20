#include "cscript.h"

#include <stdio.h>
#include <stdlib.h>

int cleanup(int temp_cnt, char **temp_filenames)
{
	for (int i = 0; i <	temp_cnt; i++) {
		if (remove(temp_filenames[i]))
			return -1;
		free(temp_filenames[i]);
	}
}
