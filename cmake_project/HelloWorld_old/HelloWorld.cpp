/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include file
#include <stdio.h>

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
    printf("HelloWorld!\n");

    int a = 10;
    int b = 2;

    int c = add(a, b);

    printf("%d + %d = %d", a, b, c);

    return 1;
}

/*---------------------------------------------------------------------------*/
/*EOF*/
