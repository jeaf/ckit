#ifndef NDEBUG
    enum $name_EDbgState { CONSTRUCTED = 1234567, DESTRUCTED };
#endif

typedef struct
{
    $type* buf;
    unsigned size;
    unsigned capacity;
    unsigned front;
    unsigned back;

    #ifndef NDEBUG
        enum $name_EDbgState dbgstate;
    #endif
} $name;

void   $name_ctor    ($name* d);
void   $name_dtor    ($name* d);
$type* $name_pushback($name* d);
$type* $name_front   ($name* d);
void   $name_popfront($name* d);

