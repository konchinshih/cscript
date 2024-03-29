#include "cscript.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int preprocess_code(int code_fd, int processed_fd, bool main_exist)
{
	static char buf[MAX_BUF + 1];
	off_t start = lseek(processed_fd, (size_t)0, SEEK_CUR);
	
	int header_fd = open(CODE_HEADER_FILE, O_RDONLY);
	int read_len;
	while ((read_len = read(header_fd, buf, MAX_BUF)) > 0)
		write(processed_fd, buf, read_len);
	close(header_fd);

	if (!main_exist) {
		int prefix_fd = open(CODE_PREFIX_FILE, O_RDONLY);
		while ((read_len = read(prefix_fd, buf, MAX_BUF)) > 0)
			write(processed_fd, buf, read_len);
		close(prefix_fd);
	}

	bool first_read = true;
	while ((read_len = read(code_fd, buf, MAX_BUF)) > 0) {
		if (first_read && read_len >= 2 && strstr(buf, SHEBANG_PREFIX) == buf) {
			int shebang_len = strchr(buf, '\n') - buf;
			if (!shebang_len) 
				return -1;
			memmove(buf, buf + shebang_len, (read_len -= shebang_len));
		}
		write(processed_fd, buf, read_len);
	}

	if (!main_exist) {
		int suffix_fd = open(CODE_SUFFIX_FILE, O_RDONLY);
		while ((read_len = read(suffix_fd, buf, MAX_BUF)) > 0)
			write(processed_fd, buf, read_len);
		close(suffix_fd);
	}
	
	lseek(processed_fd, start, SEEK_SET);
	return 0;
}
