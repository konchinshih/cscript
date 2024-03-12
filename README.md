# cscript

A wrapper for gcc

## Usage

There are several ways to use this program.

### From file

`test.c`
```c
!/bin/c
printf("hello, world\n");
```

Run
```sh
chmod +x test.c
./test.c
```

### From stdin

```sh
cat test.c | c
```

### From parameter

```sh
c -c 'printf("hello, world\n");'
```


