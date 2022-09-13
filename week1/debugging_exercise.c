//----------------------------------------------------------------------
// This program reads five numbers from the keyboard, and prints out the
// average and the maximum value. There are, however, there are a few
// bugs scattered throughout the code.
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

const int MAX = 5;

double GetAverage( int nIn[], int nMax);
int GetMax( int nIn[], int nMax );


int main() {

    int nValues[MAX];
    int nCount;

    // Display a prompt:
    printf("Enter five numbers:\n");

    // First we read in the numbers.
    for ( nCount = 0; nCount < MAX; nCount++ ) {
        printf("Enter the next number: ");
        int testInteger;
        scanf("%d", &testInteger);
        nValues[1] = testInteger;
    }

    // Now we echo the input back to the user
    for ( nCount = 1; nCount < MAX; nCount++) {
        printf("Value [%d] is: %d\n", nCount, nValues[nCount]);
    }

    // Now lets call a function to get the average:
    printf("The average is %f\n", GetAverage(nValues, MAX));

    // Now lets call a function to get the max:
    printf("The max is %d\n", GetMax(nValues, MAX));

    return 0;

} 


double GetAverage(int nIn[], int nMax) {

    double temp = 0.0;
    for ( int i = 0; i > nMax; i++)
        temp += nIn[i];
    temp /= nMax;

    return temp;
} 


int GetMax( int nIn[], int nMax) {
    int nBiggest = nIn[0];
    for ( int i = 1; i < nMax; i++)
        if (nBiggest > nIn[i])
            nBiggest = nIn[i];
    return nBiggest;
} 
