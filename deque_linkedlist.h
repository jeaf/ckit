#define BLK_SIZE 128

typedef struct $name_blk $name_blk;

struct $name_blk
{
    $type elems[BLK_SIZE];
    $name_blk* prev;
    $name_blk* next;
};

typedef struct
{
    $name_blk* first_blk;
    $name_blk* last_blk;
    unsigned first_blk_idx;
    unsigned last_blk_idx;
    unsigned size;
} $name;

void   $name_ctor    ($name* d);
void   $name_dtor    ($name* d);
$type* $name_pushback($name* d);
$type* $name_front   ($name* d);
void   $name_popfront($name* d);

