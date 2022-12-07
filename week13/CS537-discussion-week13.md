# FSCK

## Purpose

The system utility fsck (file system consistency check) is a tool for checking the consistency of a file system in Unix and Unix-like operating systems.

## Syntax

`fsck [ -n ] [ -p ] [ -y ] [ -dBlockNumber ] [ -f ] [ -ii-NodeNumber ] [ -o Options ] [ -tFile ] [ -V VfsName ] [ FileSystem1 - FileSystem2 ... ]`

## Flags
| Item | Description |
| ----| ----| 
| -d BlockNumber	| Searches for references to a specified disk block.  |
| -f	| Performs a fast check. The -f flag prompts the fsck command not to check file systems that were unmounted successfully. | 
| -i NodeNumber	| Searches for references to a specified i-node. | 
| -n | Assumes a no response to all questions asked by the fsck command; does not open the specified file system for writing.| 
| -o | Passes comma-separated options to the fsck command. |
| -p | Does not display messages about minor problems but fixes them automatically. |
| -t File	| Specifies a File parameter as a scratch file on a file system other than the one being checked. |
| -V VfsName	| Uses the description of the virtual file system specified by the VFSName variable for the file system instead of using the /etc/filesystems file to determine the description. | 
| -y | Assumes a yes response to all questions asked by the fsck command. | 

## Usage

The **fsck** command checks and interactively repairs inconsistent file systems. You should run this command before mounting any file system. Normally, the file system is consistent, and the **fsck** command merely reports on the number of files, used blocks, and free blocks in the file system. If the file system is inconsistent, the **fsck** command displays information about the inconsistencies found and prompts you for permission to repair them.

The fsck command checks for the following inconsistencies:

- Blocks or fragments allocated to multiple files.
- i-nodes containing block or fragment numbers that overlap.
- i-nodes containing block or fragment numbers out of range.
- Discrepancies between the number of directory references to - a file and the link count of the file.
- Illegally allocated blocks or fragments.
- i-nodes containing block or fragment numbers that are marked free in the disk map.
- i-nodes containing corrupt block or fragment numbers.
- A fragment that is not the last disk address in an i-node. This check does not apply to compressed file systems.
- Files larger than 32KB containing a fragment. This check does not apply to compressed file systems.
- Size checks:
  - Incorrect number of blocks.
  - Directory size not a multiple of 512 bytes.
- Directory checks:
  - Directory entry containing an i-node number marked free in the i-node map.
  - i-node number out of range.
  - Dot (.) link missing or not pointing to itself.
  - Dot dot (..) link missing or not pointing to the parent directory.
  - Files that are not referenced or directories that are not reachable.
- Inconsistent disk map.
- Inconsistent i-node map.


## Example

1. To check all the default file systems, enter:

```
fsck
```

This command checks all the file systems marked check=true in the /etc/filesystems file. This form of the fsck command asks you for permission before making any changes to a file system.

2. To fix minor problems with the default file systems automatically, enter:

```
fsck -p
```

3. To check a specific file system, enter:

```
fsck /dev/hd1
```

This command checks the unmounted file system located on the /dev/hd1 device.


# Project 4

- ufs.h, mfs.h, upd.c, udp.h  these four files are provided
- server.c: server code, takes two command line arguments: port number and file system image. It should read all the metadata of file system and keep it in memory. Then, it waits for client requests indefinitely, process them, and reply to the client.
- mfs.c (you need to create this file): contains the implementation of the client library, MFS_Init(), MFS_Lookup(), MFS_Stat(), MFS_Write(), MFS_Read(), MFS_Creat(), MFS_Unlink(), and MFS_Shutdown()
- Makefile: should build the server executable and shared library libmfs.so

Notice: always call `fsync()` after you make some change to the file system.



#!/bin/bash
base=~cs537-1/tests/p4
killall server
pkill -9 -u $USER -f "python /u/c/s/cs537-1/tests/p4/project4.py"
python $base/project4.py --test-path $base $@ | tee -i runtests.log
exit $?
~


/home/jinlang/cs537/p5/linux


import toolspath
from testing import BuildTest

tester_files = ["shutdown", "creat", "write", "dirs", "complex"]

build_test = BuildTest
build_test.targets = ["server", "libmfs.so"]

all_tests = list()
for f in tester_files:
  module = __import__(f)
  all_tests.extend(module.test_list)

from testing.runtests import main
main(build_test, all_tests)
~

/home/jinlang/cs537/p5/linux

/home/cs537-1/tests/tools/tester


server: no process found
Traceback (most recent call last):
  File "/home/cs537-1/tests/p4/project4.py", line 2, in <module>
    from testing import BuildTest
  File "/home/cs537-1/tests/tools/testing/__init__.py", line 2, in <module>
    from test import Test
ImportError: cannot import name 'Test' from 'test' (/usr/lib/python3.10/test/__init__.py)