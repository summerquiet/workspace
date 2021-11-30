/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include <stdio.h>

#ifndef CXX_SAMPLE_ALGORITHM_H
#   include "Sample_Algorithm.h"
#endif

/*---------------------------------------------------------------------------*/
// Add
int add(int a, int b)
{
    return a + b;
}

/*---------------------------------------------------------------------------*/
// Main
int main(int argc, char** argv)
{
    // 1. 
    printf("HelloWorld!\n");

    // 2.
    int a = 10, b = 2;
    int c = add(a, b);
    printf("%d + %d = %d\n", a, b, c);

    // 3.
    Sample_Algorithm algorithm;
    int d = algorithm.sub(a, b);
    printf("%d - %d = %d\n", a, b, d);

    // 4.
    int x = 3;
    int y = 3 * x++ >> 1;
    printf("x = %d, y = %d\n", x, y);

    // Return
    return 0;

    // Thank you 
}

/*---------------------------------------------------------------------------*/
 /*EOF*/
