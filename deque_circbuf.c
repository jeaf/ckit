void $name_ctor($name* d)
{
    assert(d);
    memset(d, 0, sizeof($name));
}

void $name_dtor($name* d)
{
    assert(d);
    free(d->buf);
}

$type* $name_pushback($name* d)
{
    assert(d);
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
        }
    }
    assert(d->capacity > d->size);
    d->back = (d->back + 1) % d->capacity;
    ++d->size;
    $ctor{d->buf[d->back]}
    return &d->buf[d->back];
}

$type* $name_front($name* d)
{
    assert(d);
    assert(d->size > 0);
    return &d->buf[d->front];
}

void $name_popfront($name* d)
{
    assert(d);
    assert(d->size > 0);
    $dtor{d->buf[d->front]}
    --d->size;
    d->front = (d->front + 1) % d->capacity;
}

