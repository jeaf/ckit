void swap(int* v1, int* v2)
{
    assert(v1);
    assert(v2);

    int tmp = *v2;
    *v2 = *v1;
    *v1 = tmp;
}

void heapify(int a[], int count, int root)
{
    assert(a);
    assert(root >= 0);
    assert(root < count);

    // Compute the indices for the left and right child
    int left  = 2 * root + 1;
    int right = 2 * root + 2;

    // Determine which of root,left,right is the largest
    int largest = root;
    if (left < count && a[largest] < a[left])
    {
        largest = left;
    }
    if (right < count && a[largest] < a[right])
    {
        largest = right;
    }
    if (root != largest)
    {
        swap(&a[root], &a[largest]);
        heapify(a, count, largest);
    }
}

void heapbuild(int a[], int count)
{
    assert(a);

    // Heapify each node, starting from last parent, counting backwards
    for (int i = (count - 2) / 2; i >= 0; --i)
    {
        heapify(a, count, i);
    }
}

void heappush(int a[], int count)
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
        if (a[parent] < a[i])
        {
            swap(&a[parent], &a[i]);
            i = parent;
            parent = floor((i - 1) / 2.0);
        }
        else
        {
            break;
        }
    }
}

int heappop(int a[], int count)
{
    assert(a);
    assert(count > 0);

    int top = a[0];
    swap(&a[0], &a[count - 1]);
    heapify(a, count - 1, 0);
    return top;
}

void heapsort(int a[], int count)
{
    assert(a);

    heapbuild(a, count);
    for (int i = count - 1; i > 0; --i)
    {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
}

void heapprint(int a[], int count)
{
    assert(a);

    int* i = a;
    unsigned c = 1;
    while (i != a+count)
    {
        for (unsigned k = 0; k < c && i != a+count; ++k)
        {
            printf("%d:%d    ", c+k, *i++);
        }
        printf("\n");
        c *= 2;
    }
}

