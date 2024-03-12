# cscript

A wrapper for gcc

## Usage

There are several ways to use this program.

1. From file

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

2. From stdin

```sh
cat test.c | c
```

3. From parameter

```sh
c -c 'printf("hello, world\n");'
```


