# Hash Hash Hash
In this lab, the goal is to fix an implementation of a hash table for multithreaded enviorments. Version 1 (`hash_table_v1`) employs a global mutex to ensure thread safety, but significantly degrades performance as a result. Version 2 (hash_table_v2) improves the performance of version 1 by introducing locking at the entry-level of a hash table.

## Building
```shell
make
```

## Running
```shell
./hash-table-tester -t <number of threads> -s <number of entries>
```
Upon execution, the program will output the performance of the hash table implementation and the number of missing hash table elements when a hash table is implemented using that version. Example output may look something like this:
```shell
./hash-table-tester -t 8 -s 50000
Generation: 130,340 usec
Hash table base: 1,581,974 usec
  - 0 missing
Hash table v1: 359,149 usec
  - 28 missing
Hash table v2: 396,051 usec
  - 24 missing
```

## First Implementation
In the `hash_table_v1_add_entry` function, I added global mutex lock to synchronize access to the hash table. The lock prevents multiple threads from adding entries to the hash table at the same time ensuring thread safety and stopping race conditions. 
When an entry is being added to the hash table, the global mutex lock is locked, preventing other entries from simultaneously being added. When the entry adding process is complete, the mutex is unlocked. 

### Performance
```shell
./hash-table-tester -t 8 -s 50000
Generation: 156,496 usec
Hash table base: 1,117,108 usec
  - 0 missing
Hash table v1: 3,555,381 usec
  - 0 missing
...
```
Version 1 is a little slower than the base version. Adding a global mutex to the hash table implementation add significant overhead to the performance as seen by the results. Each thread must wait for the mutex to be released before it can do any operations (i.e. add a new entry to the hash table). Since each thread is working sequentially and there is not parallel work, thread creation, destruction, unlocking, and locking is just extra overhead on top of the sequential hash table implementation in base version.

## Second Implementation
In the `hash_table_v2_add_entry` function, I added a lock to each hash table entry. This version reduces overhead by giving each entry its own lock which allows multiple threads to operate on differnt entries of the hash table at the same time. 

### Performance
```shell
./hash-table-tester -t 8 -s 50000
Generation: 156,496 usec
Hash table base: 1,117,108 usec
  - 0 missing
Hash table v1: 3,555,381 usec
  - 0 missing
Hash table v2: 301,756 usec
  - 0 missing
```

To measure the speedup of version 2 in comparison to version 1 and the base version, I ran 3 trials of 8 threads and 50,000 items which yeilded the following results:
| Trial   | Base Time | v1 Time | v2 Time |
| ------- | --------- | ------- | ------- |
| Trial 1 | 1.18s     | 2.54s   | 0.28s   |
| Trial 2 | 0.84s     | 2.85s   | 0.16s   |
| Trial 3 | 1.18s     | 2.27s   | 0.26s   |
| Average | 1.07s     | 2.55s   | 0.23s   |
In comparison to the base version, version 2 is `4.65` times faster.
In comparison to version 1, version 2 is `11.1` times faster.

## Cleaning up
```shell
make clean
```