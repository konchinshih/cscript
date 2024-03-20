#ifndef __CSCRIPT_H__
#define __CSCRIPT_H__

#include <unistd.h>
#include <stdbool.h>

#define CXX_PATH "/bin/gcc"
#define CXX "gcc"

#ifdef DEBUG
#define CONFIG_DIR "/storage/konchin/cscript/config/"
#else
#define CONFIG_DIR "/etc/cscript/"
#endif

#define GCC_PARAMS_FILE CONFIG_DIR "gcc_params"

#define CODE_HEADER_FILE CONFIG_DIR "header"
#define CODE_PREFIX_FILE CONFIG_DIR "prefix"
#define CODE_SUFFIX_FILE CONFIG_DIR "suffix"

#define FILENAME_TEMPLATE "/tmp/cscript-XXXXXX"

#define MAX_BUF 100000

#ifdef DEBUG
#include <stdio.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#else
#define debug(...) 
#endif

int /* status */
parse_argv(int argc, char **argv,
           int *source_fd, char **target_argv,
           int *temp_cnt, char **temp_filenames);

int /* cnt */ 
get_gcc_params(char **gcc_argv);

int /* code_fd */
read_code(int source_fd, int code_fd, bool *main_exist);

int /* status */
preprocess_code(int code_fd, int processed_fd, bool main_exist);

int /* status */ 
compile(int code_fd, char* target_filename);

int /* status */
run(char *path, char **argv);

int /* status */ 
cleanup(int temp_cnt, char **temp_filenames);

char * /* filename */
mktmp(int *fd);

#endif
