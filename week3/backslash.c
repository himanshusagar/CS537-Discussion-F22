#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[] = "almost every programmer should know memset!";
    memset (str,'-',6);
    puts (str);
    getchar();

    int init_size = 10;
    char *ptr = malloc( sizeof( char ) * init_size);
    //Assume G is garbage. Since actual garbage in not printable on terminal.
    memset(ptr , 'G' , init_size);
    printf("ptr looks like %s \n" , ptr);
    getchar();

    memset(ptr , 'A' , 7);
    ptr[4] = '\0';

    printf("Length of string %s is %ld ..... but ptr[%d] = %c \n" , ptr ,  strlen(ptr) , 5 , ptr[5]);
    getchar();

    printf("Similarly ptr[%d] = %c \n" , 6 , ptr[6]);
    getchar();

    printf("But ptr[%d] = %c . It's garbage \n" , 7 , ptr[7]);
    getchar();

    printf("This is how ptr looks --- ");
    for (int i = 0; i < init_size ; ++i)
    {
        printf("%c" , ptr[i]);
    }
    printf("\n\n");

    char append[] = "BBBB";
    strcat(ptr , append);
    printf("After append string %s's length is %ld \n" , ptr ,  strlen(ptr) );
    getchar();

    printf("So, ptr[%d] is still %c \n" , 9 ,  ptr[9]);
    getchar();

    printf("After append, this is how ptr looks --- ");
    for (int i = 0; i < init_size ; ++i)
    {
        printf("%c" , ptr[i]);
    }
    printf("\n");

    free(ptr);
    return 0;
}