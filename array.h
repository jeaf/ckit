typedef struct
{
    $type* data;
    int  size;
    int  capacity;
} array_$type;

void array_$type_construct(array_$type* a);
void array_$type_pushback(array_$type* a, $type val);
void array_$type_print($type a[], int count);
void array_$type_destruct(array_$type* a);

