#include "ckit.h"

#include <stdio.h>

void test_array()
{
    printf("Testing array\n");
    array a;
    array_construct(&a);
    array_pushback(&a, 3);
    array_pushback(&a, 7);
    array_print(a.data, a.size);
    array_destruct(&a);
}

void test_heap()
{
    printf("Testing heap\n");
    int a[] = {3,4,9,1,2,13,8,14};
    int a_size = sizeof(a) / sizeof(int);
    heapsort(a, a_size);
    array_print(a, a_size);
}

int main()
{
    test_array();
    test_heap();
    return 0;
}

