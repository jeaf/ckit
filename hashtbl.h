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
} hashtbl_$type;

void   hashtbl_$type_ctor  (hashtbl_$type* a);
void   hashtbl_$type_dtor  (hashtbl_$type* a);

$type* hashtbl_$type_get   (hashtbl_$type* a, $key_type key);
$type* hashtbl_$type_lookup(hashtbl_$type* a, $key_type key);
void   hashtbl_$type_erase (hashtbl_$type* a, $key_type key);

void   hashtbl_$type_print (hashtbl_$type* a);

