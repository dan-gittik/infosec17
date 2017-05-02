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
    if not 2 <= len(argv) <= 3:
        print('USAGE: %s <asm-file> [bin-file]' % argv[0])
        return -1
    if len(argv) == 2:
        path = argv[1]
        print(repr(assemble_file(path)))
    if len(argv) == 3:
        source_path = argv[1]
        target_path = argv[2]
        with open(target_path, 'wb') as writer:
            writer.write(assemble_file(source_path))


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
