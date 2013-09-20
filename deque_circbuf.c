void $name_ctor($name* d)
{
    assert(d);
    memset(d, 0, sizeof($name));
    #ifndef NDEBUG
        d->dbgstate = CONSTRUCTED;
    #endif
}

void $name_dtor($name* d)
{
    assert(d);
    free(d->buf);
    #ifndef NDEBUG
        d->dbgstate = DESTRUCTED;
    #endif
}

$type* $name_pushback($name* d)
{
    assert(d);
    assert(d->dbgstate == CONSTRUCTED);
    if (d->size == d->capacity)
    {
        if (d->capacity == 0)
       {
            d->capacity = 1;
            d->buf      = calloc(1, sizeof($type));
        }
        else
        {
            d->capacity *= 2;
            d->buf      = realloc(d->buf, sizeof($type) * d->capacity);
            assert(d->buf);
        }
    }
    assert(d->capacity > d->size);
    d->back = (d->back + 1) % d->capacity;
    ++d->size;
    assert(d->back < d->capacity);
    $ctor{d->buf[d->back]}
    return &d->buf[d->back];
}

$type* $name_front($name* d)
{
    assert(d);
    assert(d->dbgstate == CONSTRUCTED);
    assert(d->size > 0);
    assert(d->front < d->capacity);
    return &d->buf[d->front];
}

void $name_popfront($name* d)
{
    assert(d);
    assert(d->dbgstate == CONSTRUCTED);
    assert(d->size > 0);
    assert(d->front < d->capacity);
    $dtor{d->buf[d->front]}
    --d->size;
    d->front = (d->front + 1) % d->capacity;
}

