GDB Tutorial

debugging_example.c can be used to demonstrate this stuff, the example commands below all work
with the file

Must compile file with -g flag to enable debugging support

    $ gcc -g debugging_example.c

Start session and open a file in the debugger


    $ gdb a.out

Can also do
    
    $ gdb
    $ file a.out

To run the program, do

    (gdb) run 

Breakpoints allow you to essentially hit pause during a files execution. In execution, if we reach a breakpoint, gdb will pause execution
and prompt for another command

    (gdb) break 11
    (gdb) b 12

    Adds a breakpoint in file1.c/the loaded file at line 6

    (gdb) break my_func

    Adds a breakpoint at the start of my_func()

    Can delete them with the delete command

    (gdb) delete 3
    (gdb) d 2

    This will delete breakpoint 1

To resume execution, use the continue command

    (gdb) continue
    (gdb) c

One debugging strategy is to add a breakpoint before a code block that is behaving incorrectly for some reason, then step through the block
line by line. The step command allows you to do that

    (gdb) step 
    (gdb) s

Typing step over and over gets tedious, you can just hit enter to repeat the previous command

Printing values of variables can be helpful in figuring out logic errors. You can do so like this

    (gdb) print my_var
    (gdb) p my_var

Backtrace lets you print the stack trace of function calls that lead up to the point of execution you are at. Very useful
when dealing with seg faults

    (gdb) backtrace
    (gdb) bt

To exit gdb, use the quit command

    (gdb) quit 
    (gdb) q 


The debugging_exercise.c file can be given to students to work on. The bugs are:
* line 27, everything gets stored in index 1
* line 51, should be less than as the condition
* line 62, should be <

---------------------------------------------------------------------------\

Random c questions

What’s wrong with this code?

```c
int *p = malloc(sizeof(int));
p = malloc(2 * sizeof(int));
*p = 0;
p++;
*p = 1;
```

How can you free first memory block


This function is supposed to swap two doubles; does it work?

```c
void swap_double(double* a, double* b) {
double* tmp = a;
a = b;
b = tmp;
}
```

No, only works within the scope of the function.


This function is supposed to allocate n bytes of memory and make it available to the caller;
does it work?

```c
void str_alloc(char *str, int n) {
str = (char *) malloc(n * sizeof(char));
}
```

No, need to pass by reference not by copy, would need to pass in **str


What will be the output of this code?

```c
int *p = NULL;
p = malloc(10 * sizeof(int));
printf("%d\n",sizeof(p));
```

8, sizeof will return the size of the ptr not the memory block


Is this code correct?
```c
int x;
char * st = malloc(31);
scanf("%d", &x);
scanf("%30s", st);

```

Yes