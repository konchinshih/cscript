#include "cscript.h"

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *mktmp(int *fd)
{
	char *filename = malloc(strlen(FILENAME_TEMPLATE) + 1);
	strcpy(filename, FILENAME_TEMPLATE);
	*fd = mkstemp(filename);
	return filename;
}
