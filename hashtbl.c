void $name_grow($name* a)
{
    $name new_ht;
    new_ht.size     = 0;
    new_ht.capacity = a->capacity << 1;
    new_ht.items    = calloc(new_ht.capacity, sizeof(hashtbl_item));
    for (unsigned i = 0; i < a->capacity; ++i)
    {
        if (a->items[i].state == VALID)
        {
            *$name_lookup(&new_ht, a->items[i].key) = a->items[i].value;
        }
    }
    free(a->items);
    *a = new_ht;
}

void $name_ctor($name* a)
{
    assert(a);
    a->size     = 0;
    a->capacity = 8;
    a->items    = calloc(a->capacity, sizeof(hashtbl_item));
}

void $name_dtor($name* a)
{
    assert(a);
    free(a->items);
    memset(a, 0, sizeof($name));
}

$type* $name_get($name* a, $key_type key)
{
    assert(a);
    assert(a->capacity > 0);
    assert(a->items);
    assert((a->capacity & (a->capacity - 1)) == 0); // must be power of 2
    
    unsigned hashidx = $hash{key} & (a->capacity - 1);
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

        // Slot is valid. If the key matches, return it
        else if (i->state == VALID && $equals{i->key, key})
        {
            return &i->value;
        }
    }

    // Value not found
    return 0;
}

$type* $name_lookup($name* a, $key_type key)
{
    assert(a);
    assert(a->capacity > 0);
    assert(a->items);
    assert((a->capacity & (a->capacity - 1)) == 0); // must be power of 2
    
    // First check if we need to grow the hashtbl
    if (((float)a->size / a->capacity) > 0.3)
    {
        $name_grow(a);
    }
    
    unsigned hashidx = $hash{key} & (a->capacity - 1);
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

        // Slot is valid. If the key matches, return it
        else if ($equals{i->key, key})
        {
            return &i->value;
        }
    }

    // If we get here, it means the value was not found. Insert and return it.
    assert(insert_idx < a->capacity);
    a->items[insert_idx].state = VALID;
    a->items[insert_idx].key   = key;
    $ctor{a->items[insert_idx].value};
    a->size++;
    return &a->items[insert_idx].value;
}

void $name_erase($name* a, $key_type key)
{
    assert(a);
    if (a->size == 0) return;
    unsigned hashidx = $hash{key} & (a->capacity - 1);
    unsigned offset = 0;
    while (offset < a->capacity)
    {
        unsigned idx = (hashidx + offset++) % a->capacity;
        hashtbl_item* i = &a->items[idx];

        // Slot is valid and with a matching key, ditch it
        if (i->state == VALID && $equals{i->key, key})
        {
            i->state = ERASED;
            $dtor{i->value}
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

void $name_print($name* a)
{
    assert(a);
    printf("[");
    for (unsigned i = 0; i < a->capacity; ++i)
    {
        if (a->items[i].state == VALID)
        {
            $print_key{a->items[i].key};
            printf(":");
            $print{a->items[i].value};
            printf(",");
        }
    }
    printf("]");
}

