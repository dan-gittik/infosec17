import os
import re
import subprocess
import sys
import tempfile

import assemble


def find_gadget(gadget):
    # gdb <program> --batch -ex <command> -ex <command> ... loads <program> into gdb and runs all the <commands> on it.
    output = subprocess.check_output(['gdb', './a', '--batch',
        '-ex', 'break main',
        '-ex', 'run',
        '-ex', 'info files',
        '-ex', 'quit',
    ])
    # For each text segment (a line containing ".text") find its start and end addresses, dump that memory and load it.
    text_segments = []
    for line in output.splitlines():
        if '.text' in line:
            start, end = re.search('0x([0-9a-f]*) - 0x([0-9a-f]*)', line).groups()
            start, end = int(start, 16), int(end, 16)
            print('collecting text segment from 0x%08x to 0x%08x...' % (start, end))
            with tempfile.NamedTemporaryFile() as temp_file:
                subprocess.check_output(['gdb', './a', '--batch',
                    '-ex', 'break main',
                    '-ex', 'run',
                    '-ex', 'dump memory %s %s %s' % (temp_file.name, start, end),
                    '-ex', 'quit',
                ])
                with open(temp_file.name, 'rb') as reader:
                    data = reader.read()
                text_segments.append((data, start))
    # Assemble the gadget.
    if not gadget.endswith('RET'):
        gadget += '; RET'
    opcodes = assemble.assemble_data(gadget)
    # For each text segment, find all the offsets containing these opcodes and compute their virtual address.
    addresses = []
    for data, start in text_segments:
        offset = 0
        while True:
            offset = data.find(opcodes, offset+1)
            if offset == -1:
                break
            address = start + offset
            # Don't bother with addresses that contain null bytes.
            if '00' in hex(address):
                continue
            print('found gadget %r in address 0x%08x' % (gadget, address))
            addresses.append(address)
    if not addresses:
        raise RuntimeError('gadget %r not found' % gadget)
    return addresses


def main():
    if len(sys.argv) != 2:
        print('USAGE: %s <gadget>' % sys.argv[0])
        return -1
    find_gadget(sys.argv[1])


if __name__ == '__main__':
    main()
