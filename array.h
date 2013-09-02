typedef struct
{
    $type*   data;
    unsigned size;
    unsigned capacity;
} array_$type;

void   array_$type_ctor    (array_$type* a);
void   array_$type_dtor    (array_$type* a);

$type* array_$type_pushback(array_$type* a);
void   array_$type_popback (array_$type* a);

void   array_$type_print   (array_$type* a);

