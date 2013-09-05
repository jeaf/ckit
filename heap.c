void heapswap_$type($type* v1, $type* v2)
{
    assert(v1);
    assert(v2);

    $type tmp = *v2;
    *v2 = *v1;
    *v1 = tmp;
}

void heapify_$type($type a[], int count, int root)
{
    assert(a);
    assert(root >= 0);
    assert(root < count);

    // Compute the indices for the left and right child
    int left  = 2 * root + 1;
    int right = 2 * root + 2;

    // Determine which of root,left,right is the largest
    int largest = root;
    if (left < count && $lessthan{a[largest], a[left]})
    {
        largest = left;
    }
    if (right < count && $lessthan{a[largest], a[right]})
    {
        largest = right;
    }
    if (root != largest)
    {
        heapswap_$type(&a[root], &a[largest]);
        heapify_$type(a, count, largest);
    }
}

void heapbuild_$type($type a[], int count)
{
    assert(a);

    // Heapify each node, starting from last parent, counting backwards
    for (int i = (count - 2) / 2; i >= 0; --i)
    {
        heapify_$type(a, count, i);
    }
}

void heappush_$type($type a[], int count)
{
    assert(a);
    assert(count > 0);

    // We assume that the last element of the array must be pushed, i.e.,
    // the actual heap consists of elements 0 to count-2, and element
    // count-1 is the element to push
    
    int i = count - 1;
    int parent = floor((i - 1) / 2.0);
    while (parent >= 0)
    {
        if ($lessthan{a[parent], a[i]})
        {
            heapswap_$type(&a[parent], &a[i]);
            i = parent;
            parent = floor((i - 1) / 2.0);
        }
        else
        {
            break;
        }
    }
}

void heappop_$type($type a[], int count)
{
    assert(a);
    assert(count > 0);

    heapswap_$type(&a[0], &a[count - 1]);
    heapify_$type(a, count - 1, 0);
}

void heapsort_$type($type a[], int count)
{
    assert(a);

    heapbuild_$type(a, count);
    for (int i = count - 1; i > 0; --i)
    {
        heapswap_$type(&a[0], &a[i]);
        heapify_$type(a, i, 0);
    }
}

