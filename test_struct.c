#include "test_struct.h"

#include <stdio.h>

void print_test_struct(test_struct ts)
{
    printf("(%d,%f)", ts.a, ts.b);
}

