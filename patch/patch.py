import os


def main():
    # First, let's read the file.
    path = 'a'
    with open(path, 'rb') as reader:
        data = reader.read()
    # In Python, strings are immutable, so let's "cast" it into a bytearray.
    data = bytearray(data)
    # Let's make sure we're patching the JZ byte (this should be 0x74).
    offset = 0x41c
    assert data[offset] == 0x74
    # And now let's change it to JNZ (0x75).
    data[offset] = 0x75
    # Finally, let's write the patched file.
    path += '.patched'
    with open(path, 'wb') as writer:
        writer.write(data)
    # Make it executable and run it. Impossible!
    os.chmod(path, 0o777)
    os.execl(path, path)


if __name__ == '__main__':
    main()
