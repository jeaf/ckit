typedef struct
{
    int* data;
    int  size;
    int  capacity;
} array;

void array_construct(array* a);
void array_pushback(array* a, int val);
void array_print(int a[], int count);
void array_destruct(array* a);

