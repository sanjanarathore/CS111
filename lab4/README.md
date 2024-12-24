# Hey! I'm Filing Here

In this lab, I successfully implemented a 1 MiB ext2 filesystem image from scratch. This file system contains a root directory, a lost+found directory, a file named hello-world, and a symbolic link named hello which points to hello-world.

## Building
Run the make command to build the executable.
```shell
make
```

## Running
Run the executable using:
```shell
./ext2-create
```
Upon successful executable, the following image is created: `cs111-base.img`.

To dump the filesystem information, run the following command:
```shell
dumpe2fs cs111-base.img
```

To check that the filsystem is correct, run the following command:
```shell
fsck.ext2 cs111-base.img
```

In order to use our file system, we must mount it to a directory. Run the following commands to do so:
```shell
mkdir mnt
sudo mount -o loop cs111-base.img mnt
```

## Cleaning up
Once we are done using our file system, we must unmount it using the following commands:
```shell
sudo umount mnt
rmdir mnt
```

Run the following file to delete the executable and other files creating via building/running:
```shell
make clean
```
