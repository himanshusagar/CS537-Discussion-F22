## xv6 and GDB
To run xv6 with gdb: 

1. Change -O2 flag in Makefile to -Og

Before:

```c
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -O2...
```
After:
```c
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -Og...
```

2. Recent gdb versions will not automatically load `.gdbinit` for security purposes. You should do both:

- `echo "add-auto-load-safe-path $(pwd)/.gdbinit" >> ~/.gdbinit`. This enables the autoloading of `.gdbinit` in the current working directory.
- `echo "set auto-load safe-path /" >> ~/.gdbinit`. This enables the autoloading of every `.gdbinit`

3. In one window

```bash
$ make qemu-nox-gdb
```
3. then in another window:

```bash
$ gdb kernel
GNU gdb (Ubuntu 9.2-0ubuntu1~20.04) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
...
Type "apropos word" to search for commands related to "word"...
Reading symbols from kernel...
+ target remote localhost:29475
The target architecture is assumed to be i8086
[f000:fff0]    0xffff0:	ljmp   $0x3630,$0xf000e05b
0x0000fff0 in ?? ()
+ symbol-file kernel
```

Once GDB has connected successfully to QEMU's remote debugging stub, it retrieves and displays information about where the remote program has stopped:

 ```bash
 The target architecture is assumed to be i8086
[f000:fff0]    0xffff0:	ljmp   $0x3630,$0xf000e05b
0x0000fff0 in ?? ()
+ symbol-file kernel
 ```
QEMU's remote debugging stub stops the virtual machine before it executes the first instruction: i.e., at the very first instruction a real x86 PC would start executing after a power on or reset, even before any BIOS code has started executing.

Type the following in GDB's window:

 ```bash
 (gdb) b exec
Breakpoint 1 at 0x80100a80: file exec.c, line 12.
(gdb) c
Continuing.
 ```
These commands set a breakpoint at the entrypoint to the exec function in the xv6 kernel, and then continue the virtual machine's execution until it hits that breakpoint. You should now see QEMU's BIOS go through its startup process, after which GDB will stop again with output like this:

```bash
The target architecture is assumed to be i386
0x100800 :	push   %ebp

Breakpoint 1, exec (path=0x20b01c "/init", argv=0x20cf14) at exec.c:11
11	{
(gdb) 
```

At this point, the machine is running in 32-bit mode, the xv6 kernel has initialized itself, and it is just about to load and execute its first user-mode process, the /init program. You will learn more about exec and the init program later; for now, just continue execution:

```bash
(gdb) c
Continuing.
0x100800 :	push   %ebp

Breakpoint 1, exec (path=0x2056c8 "sh", argv=0x207f14) at exec.c:11
11	{
(gdb) 
```
The second time the exec function gets called is when the /init program launches the first interactive shell, sh.

Now if you continue again, you should see GDB appear to "hang": this is because xv6 is waiting for a command (you should see a '$' prompt in the virtual machine's display), and it won't hit the exec function again until you enter a command and the shell tries to run it. Do so by typing something like:

```bash
$ cat README
```
You should now see in the GDB window:

```bash
0x100800 :	push   %ebp

Breakpoint 1, exec (path=0x1f40e0 "cat", argv=0x201f14) at exec.c:11
11	{
(gdb) 
```

GDB has now trapped the exec system call the shell invoked to execute the requested command.

Now let's inspect the state of the kernel a bit at the point of this exec command.

```bash
(gdb) p argv[0]
(gdb) p argv[1]
(gdb) p argv[2]
```

Let's continue to end the cat command.
```bash
(gdb) c
Continuing.
```
