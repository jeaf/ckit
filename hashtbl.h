typedef enum {FREE, ERASED, VALID} hashtbl_item_state;
typedef struct
{
    hashtbl_item_state state;
    $key_type          key;
    $type              value;
} hashtbl_item;

typedef struct
{
    hashtbl_item* items;
    unsigned      size;
    unsigned      capacity;
} $name;

void   $name_ctor  ($name* a);
void   $name_dtor  ($name* a);

$type* $name_get   ($name* a, $key_type key);
$type* $name_lookup($name* a, $key_type key);
void   $name_erase ($name* a, $key_type key);

void   $name_print ($name* a);

