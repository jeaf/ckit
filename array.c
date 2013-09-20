void $name_ctor($name* a)
{
    assert(a);
    memset(a, 0, sizeof($name));
}

void $name_dtor($name* a)
{
    assert(a);
    for (unsigned i = 0; i < a->size; ++i)
    {
        $dtor{a->data[i]}
    }
    free(a->data);
    #ifndef NDEBUG
        memset(a, 0, sizeof($name));
    #endif
}

$type* $name_pushback($name* a)
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
    $ctor{a->data[a->size]}
    return &a->data[a->size++];
}

void $name_popback($name* a)
{
    assert(a);
    assert(a->size);
    --a->size;
    $dtor{a->data[a->size]}
}

void $name_print($name* a)
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
    printf("]");
}

