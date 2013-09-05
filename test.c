#include "ckit.h"
#include "test_struct.h"

#include <stdio.h>

void test_array()
{
    printf("Testing array\n");
    array_int a;
    array_int_ctor(&a);
    *array_int_pushback(&a) = 3;
    *array_int_pushback(&a) = 7;
    array_int_print(&a);
    array_int_dtor(&a);

    test_struct ts;
    ts.a     = 43;
    ts.b     = 9.4f;
    ts.c     = 'z';
    ts.d[22] = 3.0;
    array_test_struct b;
    array_test_struct_ctor(&b);
    *array_test_struct_pushback(&b) = ts;
    ts.a = 987;
    ts.b = 0.0f;
    *array_test_struct_pushback(&b) = ts;
    array_test_struct_print(&b);
    array_test_struct_dtor(&b);
}

void test_heap()
{
    printf("Testing heap\n");
    array_int a;
    array_int_ctor(&a);
    *array_int_pushback(&a) = 3;
    *array_int_pushback(&a) = 4;
    *array_int_pushback(&a) = 9;
    *array_int_pushback(&a) = 1;
    *array_int_pushback(&a) = 2;
    *array_int_pushback(&a) = 13;
    *array_int_pushback(&a) = 8;
    heapsort_int(a.data, a.size);
    array_int_print(&a);

    array_point ap;
    array_point_ctor(&ap);
    point p;
    p.x = 1;
    p.y = 2;
    p.z = 5;
    *array_point_pushback(&ap) = p;
    p.x = 2;
    p.z = 4;
    *array_point_pushback(&ap) = p;
    p.x = 5;
    p.z = 1;
    *array_point_pushback(&ap) = p;
    heapsort_point(ap.data, ap.size);
    array_point_print(&ap);

}

int main()
{
    test_array();
    test_heap();
    return 0;
}

