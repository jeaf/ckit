#include "ckit.h"
#include "test_struct.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define TEST_BEGIN(name)\
    bool success = true; \
    printf("Testing %s...\n", #name);

#define TEST_END\
    if (success) {\
        printf("OK\n");\
    } else {\
        printf("Failed\n");\
    }

#define CHECK(cond) \
    if (!(cond)) { \
        printf("    Error(%d): %s\n", __LINE__, #cond); \
        success = false; \
    }

void test_array()
{
    TEST_BEGIN(array);
    array_int a;
    array_int_ctor(&a);
    *array_int_pushback(&a) = 3;
    *array_int_pushback(&a) = 7;
    CHECK(a.size == 2);
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
    array_test_struct_dtor(&b);

    array_model am;
    array_model_ctor(&am);
    model* mod = array_model_pushback(&am);
    mod->id = 9876;
    point* pt = array_point_pushback(&mod->pts);
    pt->x = 3.0;
    pt->y = 6.0;
    pt->z = 9.0;
    pt = array_point_pushback(&mod->pts);
    pt->x = 4.0;
    pt->y = 7.0;
    pt->z = 99.0;
    TEST_END
}

void test_deque()
{
    TEST_BEGIN(deque)

    deque_double dd;
    deque_double_ctor(&dd);
    *deque_double_pushback(&dd) = 3.9;
    *deque_double_pushback(&dd) = 4.9;
    *deque_double_pushback(&dd) = 5.9;
    *deque_double_pushback(&dd) = 6.9;
    deque_double_popfront(&dd);
    CHECK(dd.size == 3);
    CHECK(*deque_double_front(&dd) == 4.9);
    *deque_double_pushback(&dd) = 7.9;
    deque_double_popfront(&dd);
    CHECK(dd.size == 3);
    CHECK(*deque_double_front(&dd) == 5.9);
    *deque_double_pushback(&dd) = 9999.999;
    *deque_double_pushback(&dd) = 888.88;
    deque_double_popfront(&dd);
    deque_double_popfront(&dd);
    deque_double_popfront(&dd);
    deque_double_popfront(&dd);
    deque_double_popfront(&dd);
    CHECK(dd.size == 0);
    *deque_double_pushback(&dd) = 1.123456;
    CHECK(*deque_double_front(&dd) == 1.123456);

    deque_double_dtor(&dd);

    deque_ui dui;
    deque_ui_ctor(&dui);
    *deque_ui_pushback(&dui) = UIE_MOUSEDOWN;
    *deque_ui_pushback(&dui) = UIE_MOUSEUP;
    CHECK(dui.size == 2);
    CHECK(*deque_ui_front(&dui) == UIE_MOUSEDOWN);
    deque_ui_dtor(&dui);

    TEST_END
}

void test_hashtbl()
{
    TEST_BEGIN(hashtbl)
    hashtbl_int a;
    hashtbl_int_ctor(&a);
    key_struct k = {1,2};
    *hashtbl_int_lookup(&a, k) = -1;
    k.a = 3;
    *hashtbl_int_lookup(&a, k) = 3;
    CHECK(*hashtbl_int_lookup(&a, k) == 3);
    CHECK(*hashtbl_int_get(&a, k) == 3);
    k.a = 999;
    CHECK(!hashtbl_int_get(&a, k));

    // Add stuff until table needs to grow
    *hashtbl_int_lookup(&a, k) = 2;
    k.b = 88;
    *hashtbl_int_lookup(&a, k) = 4;
    k.b = 87;
    *hashtbl_int_lookup(&a, k) = 5;
    k.b = 86;
    *hashtbl_int_lookup(&a, k) = 6;
    k.b = 85;
    *hashtbl_int_lookup(&a, k) = 7;
    k.b = 84;
    *hashtbl_int_lookup(&a, k) = 8;

    // Remove an item and check if it was removed
    hashtbl_int_erase(&a, k);
    CHECK(!hashtbl_int_get(&a, k))

    TEST_END
}

void test_heap()
{
    TEST_BEGIN(heap)
    array_int a;
    array_int_ctor(&a);
    *array_int_pushback(&a) = 3;
    *array_int_pushback(&a) = 9;
    *array_int_pushback(&a) = 1;
    *array_int_pushback(&a) = 13;
    *array_int_pushback(&a) = 8;
    heapsort_int(a.data, a.size);
    CHECK(a.data[0] == 1)
    CHECK(a.data[1] == 3)
    CHECK(a.data[2] == 8)
    CHECK(a.data[3] == 9)
    CHECK(a.data[4] == 13)

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
    TEST_END
}

int main()
{
    test_array();
    test_deque();
    test_hashtbl();
    test_heap();
    return 0;
}

