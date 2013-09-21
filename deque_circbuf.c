#define $name_ASSERT_BASE                      \
    assert(d);                                 \
    assert(d->dbgstate == CONSTRUCTED);        

#define $name_ASSERT_NOTEMPTY                  \
    assert(d->buf);                            \
    assert(d->size     >  0);                  \
    assert(d->size     <= d->capacity);        \
    assert(d->front    <  d->capacity);        \
    assert(d->back     <  d->capacity);        \
    assert(d->size < 2 || d->front != d->back);\
    assert(d->size > 1 || d->front == d->back);

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
    $name_ASSERT_BASE

    free(d->buf);
    #ifndef NDEBUG
        d->dbgstate = DESTRUCTED;
    #endif
}

$type* $name_pushback($name* d)
{
    $name_ASSERT_BASE

    // If the buffer is full, we need to resize
    if (d->size == d->capacity)
    {
        // When the capacity is 0, it is a special case
        if (d->capacity == 0)
        {
            d->capacity = 1;
            d->buf      = malloc(sizeof($type) * d->capacity);
        }
        else
        {
            unsigned old_capacity = d->capacity;
            d->capacity *= 2;
            d->buf      = realloc(d->buf, sizeof($type) * d->capacity);
            assert(d->buf);

            // If the buffer is full, and front is 0, it means that the buf
            // was filled like a normal array (i.e., only with pushbacks),
            // so we don't need to move stuff around as much. We only handle the
            // case when front was not 0.
            if (d->front != 0)
            {
                // We need to move the data between front and old capacity
                // to between new front and new capacity
                memcpy(&d->buf[d->capacity - (old_capacity - d->front)],
                       &d->buf[d->front],
                       sizeof($type) * (old_capacity - d->front));
                d->front = d->capacity - (old_capacity - d->front);
            }
        }
    }
    assert(d->capacity > d->size);
    if (d->size == 0)
    {
        d->front = 0;
        d->back  = 0;
    }
    else
    {
        d->back = (d->back + 1) % d->capacity;
    }
    ++d->size;
    
    $name_ASSERT_NOTEMPTY

    $ctor{d->buf[d->back]}
    return &d->buf[d->back];
}

$type* $name_front($name* d)
{
    $name_ASSERT_BASE
    $name_ASSERT_NOTEMPTY

    return &d->buf[d->front];
}

void $name_popfront($name* d)
{
    $name_ASSERT_BASE
    $name_ASSERT_NOTEMPTY

    $dtor{d->buf[d->front]}
    --d->size;
    d->front = (d->front + 1) % d->capacity;
}

