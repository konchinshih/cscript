#include "cscript.h"

#include <string.h>
#include <unistd.h>

int read_code(int source_fd, int code_fd, bool *main_exist)
{
	static char buf[(MAX_BUF << 1) + 1];
	off_t start = lseek(code_fd, (size_t)0, SEEK_CUR);
	int read_len;
	while ((read_len = read(source_fd, buf, MAX_BUF)) > 0) {
		if (buf[read_len - 1] == '\0')
			read_len--;
		write(code_fd, buf, read_len);
		if (strstr(buf, "main("))
			*main_exist = true;
		memcpy(buf + read_len, buf, read_len);
		buf[read_len << 1] = '\0';
	}
	lseek(code_fd, start, SEEK_SET);
	return 0;
}
