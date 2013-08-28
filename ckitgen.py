import collections
import itertools
import json
import os.path
import re
import sys

# Load the config file (required)
if not os.path.isfile('ckit.config'):
    print 'ckit.config file is missing, please create it.'
    sys.exit(1)
with open('ckit.config', 'r') as f:
    config = json.load(f)

# The list of standard include files that we will need
std_incs = 'assert math stdio stdlib string'.split()

# The print regular expression
print_re = re.compile(r'\$print\{(.*)}')

# Read all input files
script_dir = os.path.abspath(os.path.dirname(__file__))
lines = dict()
for compname in config['components']:
    lines[compname] = dict()
    for ext in 'c h'.split():
        with open(os.path.join(script_dir, compname) + '.' + ext, 'r') as f:
            lines[compname][ext] = f.readlines()

# Write output files
with open('ckit.h', 'w') as outf_h, open('ckit.c', 'w') as outf_c:

    # Write initial stuff to both files
    outf_h.write('#ifndef CKIT_H\n#define CKIT_H\n\n')
    for inc in config['includes']:
        outf_h.write('#include "{}"\n'.format(inc))
    outf_c.write('#include "ckit.h"\n\n')
    for inc in std_incs:
        outf_c.write('#include <{}.h>\n'.format(inc))
    outf_c.write('\n')

    # Write actual content
    outf = {'c': outf_c, 'h': outf_h}
    for compname, typenames in config['components'].iteritems():
        for typename in typenames:
            for ext, f in outf.iteritems():
                for line in lines[compname][ext]:
                    line = line.replace('$type', typename)
                    line = print_re.sub(config['types'][typename]['print'], line)
                    f.write(line)

    # Write final stuff to both files
    outf_h.write('#endif\n')

