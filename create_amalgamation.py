import collections
import itertools
import re

# The list of standard include files that we will need
std_incs = 'assert math stdio stdlib string'.split()

# Other includes
oth_incs = 'test_struct'.split()

# The print regular expression
print_re = re.compile(r'\$print\{(.*)}')

# The instances of data structures we need to generate
Inst = collections.namedtuple('Inst', 'type_ print_')
instances = {'array': [Inst('int', r'printf("%d", \1)'), Inst('test_struct', r'print_test_struct(\1)')],
             'heap' : [Inst('int', r'printf("%d", \1)')]}

# Read all input files
lines = dict()
for name in instances:
    lines[name] = dict()
    for ext in 'c h'.split():
        with open(name + '.' + ext, 'r') as f:
            lines[name][ext] = f.readlines()

# Write output files
with open('ckit.h', 'w') as outf_h, open('ckit.c', 'w') as outf_c:

    # Write initial stuff to both files
    outf_h.write('#ifndef CKIT_H\n#define CKIT_H\n\n')
    for inc in oth_incs:
        outf_h.write('#include "{}.h"\n'.format(inc))
    outf_c.write('#include "ckit.h"\n\n')
    for inc in std_incs:
        outf_c.write('#include <{}.h>\n'.format(inc))
    outf_c.write('\n')

    # Write actual content
    outf = {'c': outf_c, 'h': outf_h}
    for name, insts in instances.iteritems():
        for instance in insts:
            for ext, f in outf.iteritems():
                for line in lines[name][ext]:
                    line = line.replace('$type', instance.type_)
                    line = print_re.sub(instance.print_, line)
                    f.write(line)

    # Write final stuff to both files
    outf_h.write('#endif\n')

