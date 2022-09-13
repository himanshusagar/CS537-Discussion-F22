#include <stdio.h>
#include <stdlib.h>

void my_func(){
    printf("Hello world again");
}

void seg_fault_fn2(){
//  seg fault
    int *b;
    b[2] = 1;
}

void seg_fault_fn1(){
    seg_fault_fn2();
}

int main(){
    char* str;
    // Adding a breakpoint at line 6 will prevent the print statement from executing until we continue/step
    printf("Hello world");
    
    my_func();

    int my_var = 8;
    
    my_var = 7;

    seg_fault_fn1();
}
