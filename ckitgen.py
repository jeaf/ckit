import collections
import itertools
import os.path
from pprint import pprint
import re
import sys

# The list of available templates
templates = 'array deque_linkedlist hashtbl heap'.split()

def process_config_blocks(s):
    if s.find('{') < 0:
        return s
    d     = collections.OrderedDict()
    name  = ''
    block = ''
    depth = 0
    for c in s:
        if c == '{':
            if depth > 0:
                block += c
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                d[name.strip()] = process_config_blocks(block.strip())
                name = ''
                block = ''
            else:
                block += c
        else:
            if depth == 0:
                name += c
            else:
                block += c
    return d

def load_config():
    if not os.path.isfile('ckit.config'):
        print 'ckit.config file is missing, please create it.'
        sys.exit(1)
    with open('ckit.config', 'r') as f:
        return process_config_blocks(f.read())
config = load_config()

# Add default types
config['int']    = {'print': r'printf("%d", \1);', 'lessthan': r'\1 < \2'}
config['double'] = {'print': r'printf("%f", \1);', 'lessthan': r'\1 < \2'}

# The list of standard include files that we will need
std_incs = 'assert math stdbool stdio stdlib string'.split()

# The template regular expressions
ctor_re      = re.compile(r'\$ctor\{(.*)}')
dtor_re      = re.compile(r'\$dtor\{(.*)}')
print_re     = re.compile(r'\$print\{(.*)}')
print_key_re = re.compile(r'\$print_key\{(.*)}')
lessthan_re  = re.compile(r'\$lessthan\{(.*),(.*)}')
equals_re    = re.compile(r'\$equals\{(.*),(.*)}')
hash_re      = re.compile(r'\$hash\{(.*)}')

# Read all input files
script_dir = os.path.abspath(os.path.dirname(__file__))
lines = dict()
for compname in templates:
    lines[compname] = dict()
    for ext in 'c h'.split():
        with open(os.path.join(script_dir, compname) + '.' + ext, 'r') as f:
            lines[compname][ext] = f.readlines()

# Write output files
with open('ckit.h', 'w') as outf_h, open('ckit.c', 'w') as outf_c:

    outf = {'c': outf_c, 'h': outf_h}

    # Write initial stuff to both files
    outf_h.write('#ifndef CKIT_H\n#define CKIT_H\n\n')
    outf_c.write('#include "ckit.h"\n\n')
    for inc in std_incs:
        outf_c.write('#include <{}.h>\n'.format(inc))
    outf_c.write('\n')

    # Loop through the types from the config file
    for name, attrs in config.iteritems():
        if 'struct' in attrs:
            outf_h.write('typedef struct\n{\n')
            for line in attrs['struct'].split('\n'):
                outf_h.write('    {};\n'.format(line.strip()))
            outf_h.write('} ' + name + ';\n\n')
        elif 'template' in attrs:
            template_name = attrs['template']
            typename      = attrs['type']
            for ext, f in outf.iteritems():
                for line in lines[template_name][ext]:
                    if ctor_re.search(line):
                        if 'ctor' in config[typename]:
                            line = ctor_re.sub(config[typename]['ctor'], line)
                        else:
                            continue
                    if dtor_re.search(line):
                        if 'dtor' in config[typename]:
                            line = dtor_re.sub(config[typename]['dtor'], line)
                        else:
                            continue
                    line = line.replace('$type', typename)
                    if 'key_type' in attrs:
                        key_typename = attrs['key_type']
                        line = line.replace('$key_type', key_typename)
                        if 'hash' in config[key_typename]:
                            line = hash_re.sub(config[key_typename]['hash'], line)
                        if 'equals' in config[key_typename]:
                            line = equals_re.sub(config[key_typename]['equals'], line)
                        line = print_key_re.sub(config[key_typename]['print'], line)
                    line = print_re.sub(config[typename]['print'], line)
                    if 'lessthan' in config[typename]:
                        line = lessthan_re.sub(config[typename]['lessthan'], line)
                    f.write(line)
        elif 'include' in attrs:
            outf_h.write('#include "{}"\n\n'.format(attrs['include']))

    # Write final stuff to both files
    outf_h.write('#endif\n')

