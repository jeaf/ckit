#ifndef TEST_STRUCT_H
#define TEST_STRUCT_H

typedef struct
{
    int    a;
    float  b;
    char   c;
    double d[98];
} test_struct;

void print_test_struct(test_struct ts);

#endif

