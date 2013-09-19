#define BLK_SIZE 128

typedef struct deque_$type_blk deque_$type_blk;

struct deque_$type_blk
{
    $type elems[BLK_SIZE];
    deque_$type_blk* prev;
    deque_$type_blk* next;
};

typedef struct
{
    deque_$type_blk* first_blk;
    deque_$type_blk* last_blk;
    unsigned first_blk_idx;
    unsigned last_blk_idx;
    unsigned size;
} deque_$type;

void   deque_$type_ctor    (deque_$type* d);
void   deque_$type_dtor    (deque_$type* d);
$type* deque_$type_pushback(deque_$type* d);
$type* deque_$type_front   (deque_$type* d);
void   deque_$type_popfront(deque_$type* d);

