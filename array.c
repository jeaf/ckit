void array_$type_ctor(array_$type* a)
{
    assert(a);
    memset(a, 0, sizeof(array_$type));
}

void array_$type_dtor(array_$type* a)
{
    assert(a);
    free(a->data);
    #ifndef NDEBUG
        memset(a, 0, sizeof(array_$type));
    #endif
}

$type* array_$type_pushback(array_$type* a)
{
    assert(a);
    if (a->size == a->capacity)
    {
        if (a->size) a->capacity = ceil(a->capacity * 1.5);
        else         a->capacity = 1;
        $type* newdata = malloc(a->capacity * sizeof($type));
        memcpy(newdata, a->data, a->size * sizeof($type));
        free(a->data);
        a->data = newdata;
    }
    return &a->data[a->size++];
}

void array_$type_popback(array_$type* a)
{
    assert(a);
    assert(a->size);
    --a->size;
}

void array_$type_print(array_$type* a)
{
    assert(a);
    printf("[");
    if (a->size)
    {
        $print{a->data[0]}
        for (unsigned i = 1; i < a->size; ++i)
        {
            printf(",");
            $print{a->data[i]}
        }
    }
    printf("]\n");
}

