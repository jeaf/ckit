# The list of standard include files that we will need
incs = 'assert math stdio stdlib string'.split()

with open('ckit.h', 'w') as ckit_h, open('ckit.c', 'w') as ckit_c:
    with open('array.h', 'r') as array_h, open('heap.h', 'r') as heap_h:
        ckit_h.write('#ifndef CKIT_H\n#define CKIT_H\n\n')
        for line in array_h.readlines():
            ckit_h.write(line)
        for line in heap_h.readlines():
            ckit_h.write(line)
        ckit_h.write('#endif\n')
    with open('array.c', 'r') as array_c, open('heap.c', 'r') as heap_c:
        ckit_c.write('#include "ckit.h"\n\n')
        for inc in incs:
            ckit_c.write('#include <{}.h>\n'.format(inc))
        ckit_c.write('\n')
        for line in array_c.readlines():
            ckit_c.write(line)
        for line in heap_c.readlines():
            ckit_c.write(line)

