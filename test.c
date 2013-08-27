#include "ckit.h"

#include <stdio.h>

void test_array()
{
    printf("Testing array\n");
    array_int a;
    array_int_construct(&a);
    array_int_pushback(&a, 3);
    array_int_pushback(&a, 7);
    array_int_print(a.data, a.size);
    array_int_destruct(&a);
}

void test_heap()
{
    printf("Testing heap\n");
    int a[] = {3,4,9,1,2,13,8,14};
    int a_size = sizeof(a) / sizeof(int);
    heapsort(a, a_size);
    array_int_print(a, a_size);
}

int main()
{
    test_array();
    test_heap();
    return 0;
}

