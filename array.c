#include "array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_construct(array* a)
{
    assert(a);
    a->data = malloc(1*sizeof(int));
    a->size = 0;
    a->capacity = 1;
}

void array_pushback(array* a, int val)
{
    assert(a);
    assert(a->capacity > 0);
    if (a->size == a->capacity)
    {
        a->capacity *= 2;
        int* newdata = malloc(a->capacity * sizeof(int));
        memcpy(newdata, a->data, a->size * sizeof(int));
        free(a->data);
        a->data = newdata;
    }
    a->data[a->size++] = val;
}

void array_print(int a[], int count)
{
    assert(a);
    printf("[");
    if (count > 0)
    {
        printf("%d", a[0]);
        for (unsigned i = 1; i < count; ++i)
        {
            printf(",%d", a[i]);
        }
    }
    printf("]\n");
}

void array_destruct(array* a)
{
    free(a->data);
    a->data = 0;
    a->size = 0;
    a->capacity = 1;
}


