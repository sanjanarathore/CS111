# You Spin Me Round Robin

This is a C implementation of the rouch robin scheduling algorithm given a workload and a quantum length. It uses the `TAILQ` data structure from the `sys/queue.h` library to managing processes. The workload consists as a list of processes with their respective arrival and burst times.

## Building
To compile the source code and create the rr executable, run the following command:
```shell
make
```

## Running
To execute the rr program, we need to provide two arguments: (1) the path to your file containing the workloads and (2) a quantum length in the form of an integer. 
```shell
./rr processes.txt 3
```
In this example, processes.txt is our file containing correctly formatted workloads and 3 is the quantum length.

This is an example of how processes.txt should be formatted:
```shell
4
1, 0, 7
2, 2, 4
3, 4, 1
4, 5, 4
```
Given the above inputs, the program will output the following average waiting time and response time:
```shell
Average waiting time: 7.00
Average response time: 2.75
```

## Cleaning up
To remove the binary and executable files created during the build process, run:
```shell
make clean
```
