# A Kernel Seedling
In this lab, we set up a virtual machine and wrote a kernal module that creates a file called /proc/count containing the number of current running processes on the kernel. We can access the contents of this file by running the following command: cat /proc/count.

## Building
```shell
make
```

## Running
```shell
sudo insmod proc_count.ko
cat /proc/count
```
After running the commands listed above, I got the following output: 150. This means there were 150 running processes on my kernel. 

## Cleaning Up
```shell
make clean
sudo rmmod proc_count
```

## Testing
```python
python -m unittest
```
After running the test cases, this is the output I got:
```
Ran 3 tests in 19.699s

OK
```

Report which kernel release version you tested your module on
(hint: use `uname`, check for options with `man uname`).
It should match release numbers as seen on https://www.kernel.org/.

```shell
uname -r -s -v
```
My kernel version is Linux 5.14.8-arch1-1 #1 SMP PREEMPT Sun, 26 Sep 2021 19:36:15 +0000