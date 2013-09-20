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

    if (d->size == d->capacity)
    {
        if (d->capacity == 0)
       {
            d->capacity = 1;
            d->buf      = calloc(1, sizeof($type));
        }
        else
        {
            unsigned old_capacity = d->capacity;
            d->capacity *= 2;
            d->buf      = realloc(d->buf, sizeof($type) * d->capacity);
            assert(d->buf);

            // If the buffer is full, and front is 0, it means that the buf
            // was filled like a normal array (i.e., only with pushbacks),
            // so we don't need to move stuff around as much
            if (d->front == 0)
            {
                assert(d->back + 1 < d->capacity);
                memset(&d->buf[d->back + 1],
                       0,
                       sizeof($type) * (d->capacity - d->size));
            }
            else
            {
                // We need to move the data between front and old capacity
                // to between new front and new capacity
                memcpy(&d->buf[d->capacity - (old_capacity - d->front)],
                       &d->buf[d->front],
                       sizeof($type) * (old_capacity - d->front));
                d->front = d->capacity - (old_capacity - d->front);

                // Set the memory between back and front to zero
                memset(&d->buf[d->back + 1],
                       0,
                       sizeof($type) * (d->front - d->back + 1));
            }
        }
    }
    assert(d->capacity > d->size);
    d->back = (d->back + 1) % d->capacity;
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

