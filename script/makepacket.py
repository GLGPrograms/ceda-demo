#!/usr/bin/python3

import sys
import struct

filename = sys.argv[1]
ifile = open(filename, 'rb')

content = ifile.read()

address = content[0] + content[1] * 256
data = content[2:]
size = len(data)

sys.stdout.buffer.write(struct.pack("<HH", address, size))
sys.stdout.buffer.write(data)

