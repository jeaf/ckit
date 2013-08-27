import itertools
import re

# The list of standard include files that we will need
std_incs = 'assert math stdio stdlib string'.split()

# Other includes
oth_incs = 'test_struct'.split()

# The print regular expression
print_re = re.compile(r'\$print\{(.*)}')

# The versions of data structures we need to generate
versions = {'array': 'int test_struct'.split(),
            'heap' : 'int test_struct'.split()}

# Read all input files
lines = dict()
for name in versions:
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
    for name, types in versions.iteritems():
        for t in types:
            for ext, f in outf.iteritems():
                for line in lines[name][ext]:
                    line = line.replace('$type', t)
                    line = print_re.sub(r'printf("%d", \1)', line)
                    f.write(line)

    # Write final stuff to both files
    outf_h.write('#endif\n')

