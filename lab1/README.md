## Pipe Up

This program takes replicates the behavior of a pipe operator. It takes executable names as command line arguments and executes each executable in a new process while handling I/O rediection and subsequent errors.

## Building
To build, run the following command:
```shell
make
```

## Running

Show an example run of your program, using at least two additional arguments, and what to expect

### Example: ls | cat | wc
```shell
./pipe ls cat wc
```
Output: 
```shell
      7       7      63
```

## Cleaning up

To clean up the build:
```shell
make clean
```
