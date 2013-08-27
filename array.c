void array_$type_construct(array_$type* a)
{
    assert(a);
    memset(a, 0, sizeof(array_$type));
}

void array_$type_pushback(array_$type* a, $type val)
{
    assert(a);
    if (a->size == a->capacity)
    {
        a->capacity = a->capacity * 2 + 1; // +1 is to support initial
                                           // push_back, when capacity == 0
        $type* newdata = malloc(a->capacity * sizeof($type));
        memcpy(newdata, a->data, a->size * sizeof($type));
        free(a->data);
        a->data = newdata;
    }
    a->data[a->size++] = val;
}

void array_$type_print($type a[], int count)
{
    assert(a);
    printf("[");
    if (count > 0)
    {
        $print{a[0]};
        for (unsigned i = 1; i < count; ++i)
        {
            printf(",");
            $print{a[i]};
        }
    }
    printf("]\n");
}

void array_$type_destruct(array_$type* a)
{
    assert(a);
    free(a->data);
    memset(a, 0, sizeof(array_$type));
}

