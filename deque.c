void deque_$type_ctor(deque_$type* d)
{
    assert(d);
    memset(d, 0, sizeof(deque_$type));
}

void deque_$type_dtor(deque_$type* d)
{
    assert(d);
    unsigned elem_idx = 0;
    unsigned blk_idx  = d->first_blk_idx;
    while (d->first_blk)
    {
        for (; elem_idx < d->size && blk_idx < BLK_SIZE; ++elem_idx, ++blk_idx)
        {
            $dtor{d->first_blk->elems[blk_idx]}
        }
        blk_idx = 0;
        deque_$type_blk* next = d->first_blk->next;
        free(d->first_blk);
        d->first_blk = next;
    }
}

$type* deque_$type_pushback(deque_$type* d)
{
    assert(d);
    if (!d->last_blk)
    {
        d->first_blk = calloc(1, sizeof(deque_$type_blk));
        d->last_blk = d->first_blk;
        d->first_blk_idx = 0;
        d->last_blk_idx = 0;
    }
    else if (d->last_blk_idx == (BLK_SIZE - 1))
    {
        assert(d->first_blk);
        assert(!d->first_blk->prev);
        assert(!d->last_blk->next);
        d->last_blk->next = calloc(1, sizeof(deque_$type_blk));
        d->last_blk->next->prev = d->last_blk;
        d->last_blk = d->last_blk->next;
        d->last_blk_idx = 0;
    }
    else
    {
        assert(d->first_blk);
        assert(!d->first_blk->prev);
        assert(!d->last_blk->next);
        ++d->last_blk_idx;
    }
    ++d->size;
    $ctor{d->last_blk->elems[d->last_blk_idx]}
    return &d->last_blk->elems[d->last_blk_idx];
}

$type* deque_$type_front(deque_$type* d)
{
    assert(d);
    assert(d->size > 0);
    assert(d->first_blk);
    return &d->first_blk->elems[d->first_blk_idx];
}

void deque_$type_popfront(deque_$type* d)
{
    assert(d);
    assert(d->size > 0);
    assert(d->first_blk);
    $dtor{d->first_blk->elems[d->first_blk_idx]}
    --d->size;
    if (d->size == 0)
    {
        free(d->first_blk);
        memset(d, 0, sizeof(deque_$type));
    }
    else if (d->first_blk_idx == (BLK_SIZE - 1))
    {
        d->first_blk_idx = 0;
        deque_$type_blk* new_first = d->first_blk->next;
        new_first->prev = 0;
        free(d->first_blk);
        d->first_blk = new_first;
    }
    else
    {
        ++d->first_blk_idx;
    }
}

