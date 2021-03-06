#!/usr/bin/python

import subprocess


def assemble_data(data):
    process = subprocess.Popen([
        'gcc',
        '-xassembler', '-',
        '-o', '/dev/stdout',
        '-nostdlib',
        '-Xlinker', '--oformat=binary'
    ], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    stdout, stderr = process.communicate('''
        .intel_syntax noprefix
        .globl _start
        _start:
        %s
    ''' % data)
    return stdout


def assemble_file(path):
    with open(path, 'rb') as reader:
        data = reader.read()
    return assemble_data(data)


def main(argv):
    if len(argv) != 2:
        print('USAGE: %s <asm-file>' % argv[0])
        return -1
    path = argv[1]
    print(repr(assemble_file(path)))


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
