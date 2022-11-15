# Reader Writer Lock

A readers–writer is a synchronization primitive that solves one of the readers–writers problems. An RW lock allows concurrent access for read-only operations, write operations require exclusive access. 
Multiple threads can read the data in parallel but an exclusive lock is needed for writing or modifying data. 
When a writer is writing the data, all other writers or readers will be blocked until the writer is finished writing. 
A common use might be to control access to a data structure in memory that cannot be updated atomically and is invalid (and should not be read by another thread) until the update is complete.

## Priority Policies:
RW locks can be designed with different priority policies for reader vs. writer access. The lock can either be designed to always give priority to readers (read-preferring), to always give priority to writers (write-preferring). These policies lead to different tradeoffs with regards to concurrency and starvation.

**Read-preferring RW locks**
They allow for maximum concurrency, but can lead to write-starvation if contention is high. Writer threads will starve while new reader threads will be able to acquire the lock as long as atleast one reader thread is holding the lock.

Implementation:

Initialization :

b = number of blocking readers

r = mutex used by readers

g = ensures mutual exclusion of writers. 


![Screen Shot 2022-11-15 at 13 22 39](https://user-images.githubusercontent.com/20151037/202007815-d4a38eaa-29b0-4553-8c61-e3bfb1d41ba0.png)

![Screen Shot 2022-11-15 at 13 22 49](https://user-images.githubusercontent.com/20151037/202007846-0758b1ff-3b77-4d2b-a696-cdf4c3de26f5.png)


**Write-preferring RW locks**
They avoid the problem of writer starvation by preventing any new readers from acquiring the lock if there is a writer queued and waiting for the lock. Write-preferring locks allows for less concurrency in the presence of writer threads, compared to read-preferring RW locks. 

How to modify the above solution to a write preferring lock?

Implementation using condition variables and mutex:

Initialization:

num_readers_active: the number of readers that have acquired the lock

num_writers_waiting: the number of writers waiting for access 

writer_active: whether a writer has acquired the lock 


![Screen Shot 2022-11-15 at 13 22 59](https://user-images.githubusercontent.com/20151037/202007868-dbd9b7b9-a0c4-4b92-b688-4fd4e4acc197.png)

![Screen Shot 2022-11-15 at 13 23 08](https://user-images.githubusercontent.com/20151037/202007882-491797a9-1bf9-4b66-9179-f168cfc2b828.png)


## Practice Questions on Concurrency:

Q1. Given a thread safe implementation of add() :

![Screen Shot 2022-11-15 at 14 28 51](https://user-images.githubusercontent.com/20151037/202019062-0500a634-cef6-4730-9178-ebd633f8f202.png)

Replace the lock with atomic hardware instruction CmpAndSwap(int* addr, int expect, int new) which returns 0 on failure and 1 on success.

![Screen Shot 2022-11-15 at 14 28 59](https://user-images.githubusercontent.com/20151037/202019333-8f56eff3-7689-45b0-a940-72ef414c3638.png)

Ans : Q1 val, Q2 old, Q3 old + amt, Q4 0

Q2. 

![Screen Shot 2022-11-15 at 16 00 39](https://user-images.githubusercontent.com/20151037/202034401-1fdecdd9-0867-4974-bf61-7de738cc5518.png)

Ans: m is a local variable, xchg comparison should be with 1

![Screen Shot 2022-11-15 at 16 00 29](https://user-images.githubusercontent.com/20151037/202034425-81b6b5f5-35c9-4a73-871a-77694024b59d.png)

Ans: m is a local variable

# RAID (Redundant Array of Inexpensive Disks)
A technique to use multiple disks in concert to build a faster, bigger, and more reliable disk system.
Transparently provides benefits like:
- Performance
- Capacity
- Reliability

![Screen Shot 2022-11-15 at 14 31 52](https://user-images.githubusercontent.com/20151037/202034303-64b059ce-57ec-4058-a8e2-8a6726387bad.png)

![Screen Shot 2022-11-15 at 14 32 49](https://user-images.githubusercontent.com/20151037/202034322-6024d80a-369a-48f6-ad50-e90a34ae3eb9.png)

![Screen Shot 2022-11-15 at 14 33 13](https://user-images.githubusercontent.com/20151037/202034334-16f678d9-47b1-49cb-8d91-cef2943b321d.png)

![Screen Shot 2022-11-15 at 14 34 55](https://user-images.githubusercontent.com/20151037/202033330-074a9b83-5864-4c9e-a745-03de9349cb9d.png)

![Screen Shot 2022-11-15 at 14 34 29](https://user-images.githubusercontent.com/20151037/202033316-1dbce933-795e-4daf-8f60-249d9bd074c7.png)

## Practice problem on RAID:

Q1. For this question, we’ll examine how long it takes to perform a small workload consisting of 12 writes to random
locations within a RAID. Assume that these random writes are spread “evenly” across the disks of the RAID.
To begin with, assume a simple disk model where each read or write takes D time units.
- Assume we have a 4-disk RAID-0 (striping). How long does it take to complete the 12 writes?
- How long on a 4-disk RAID-1 (mirroring)?
- How long on a 4-disk RAID-4 (parity)?
- How long on a 4-disk RAID-5 (rotated parity)?
- Now assume we have a better disk model, in which it takes S time units to perform a random seek and R
units of time to perform a full rotation; assume transfer is free. How long do the 12 random writes take to
complete on a 4-disk RAID-0?
- How long on a 4-disk RAID-1 (mirroring)?
- How long on a 4-disk RAID-4 (parity)?
- How long on a 4-disk RAID-5 (rotated parity)?

Ans : https://pages.cs.wisc.edu/~remzi/Classes/537/Fall2021/OldExams/11-fall-final-answers.pdf

