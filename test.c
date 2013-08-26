#include "heap.h"

int main()
{
    int a[] = {3,4,9,1,2,13,8,14};
    int a_size = sizeof(a) / sizeof(int);
    heapsort(a, a_size);
    heapprint(a, a_size);
    return 0;
}

