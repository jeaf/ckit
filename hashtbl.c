void hashtbl_$type_ctor(hashtbl_$type* a)
{
    assert(a);
    a->size     = 0;
    a->capacity = 8;
    a->items    = calloc(a->capacity, sizeof(hashtbl_item));
}

void hashtbl_$type_dtor(hashtbl_$type* a)
{
    assert(a);
    free(a->items);
    memset(a, 0, sizeof(hashtbl_$type));
}

$type* hashtbl_$type_get(hashtbl_$type* a, unsigned hash)
{
    assert(a);
    assert(a->capacity > 0);
    assert(a->items);
    assert((a->capacity & (a->capacity - 1)) == 0); // must be power of 2
    
    unsigned hashidx = hash & (a->capacity - 1);
    unsigned offset = 0;
    while (offset < a->capacity)
    {
        unsigned idx = (hashidx + offset++) % a->capacity;
        hashtbl_item* i = &a->items[idx];

        // Slot is free, searching is over
        if (i->state == FREE)
        {
            break;
        }

        // Slot is valid. If the hash matches, return it
        else if (i->state == VALID && i->hash == hash)
        {
            return &i->data;
        }
    }

    // Value not found
    return 0;
}

$type* hashtbl_$type_lookup(hashtbl_$type* a, unsigned hash)
{
    assert(a);
    assert(a->capacity > 0);
    assert(a->items);
    assert((a->capacity & (a->capacity - 1)) == 0); // must be power of 2
    
    unsigned hashidx = hash & (a->capacity - 1);
    unsigned offset = 0;
    unsigned insert_idx = UINT_MAX;
    while (offset < a->capacity)
    {
        unsigned idx = (hashidx + offset++) % a->capacity;
        hashtbl_item* i = &a->items[idx];

        // Slot is free, check its index for a potential insertion point,
        // and stop searching
        if (i->state == FREE)
        {
            if (idx < insert_idx) insert_idx = idx;
            break;
        }

        // Slot has been erased, check its index for a potential insertion
        // point, and keep searching
        else if (i->state == ERASED)
        {
            if (idx < insert_idx) insert_idx = idx;
        }

        // Slot is valid. If the hash matches, return it
        else if (i->hash == hash)
        {
            return &i->data;
        }
    }

    // If we get here, it means the value was not found. Insert and return it.
    assert(insert_idx < a->capacity);
    a->items[insert_idx].state = VALID;
    a->items[insert_idx].hash  = hash;
    a->size++;
    return &a->items[insert_idx].data;
}

void hashtbl_$type_erase(hashtbl_$type* a, unsigned hash)
{
    assert(a);
    if (a->size == 0) return;
    unsigned hashidx = hash & (a->capacity - 1);
    unsigned offset = 0;
    while (offset < a->capacity)
    {
        unsigned idx = (hashidx + offset++) % a->capacity;
        hashtbl_item* i = &a->items[idx];

        // Slot is valid and with a matching hash, ditch it
        if (i->state == VALID && i->hash == hash)
        {
            i->state = ERASED;
            a->size--;
            return;
        }

        // Slot is free, it means the value did not exist in the table
        else if (i->state == FREE)
        {
            return;
        }
    }
}

void hashtbl_$type_print(hashtbl_$type* a)
{
    assert(a);
    for (unsigned i = 0; i < a->capacity; ++i)
    {
        if (a->items[i].state == VALID)
        {
            printf("%d: ", a->items[i].hash);
            printf("%d,", a->items[i].data);
        }
    }
}

