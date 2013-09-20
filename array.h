typedef struct
{
    $type*   data;
    unsigned size;
    unsigned capacity;
} $name;

void   $name_ctor    ($name* a);
void   $name_dtor    ($name* a);

$type* $name_pushback($name* a);
void   $name_popback ($name* a);

void   $name_print   ($name* a);

