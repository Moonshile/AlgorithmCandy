#!/usr/bin/python

'''
This software is provided by Moonshile
Copyright (c) 2014
'''

import random, os, sys

input = ''
out = ''
for i in range(1, 100):
    if not os.path.isfile('b-%d.in'%i):
        input = 'b-%d.in'%i
        out = 'b-%d.out'%i
        break
fin = open(input, 'w')
fout = open(out, 'w')
MAX = 1000000000000000000;
line = 1
if len(sys.argv) == 2:
    line = int(sys.argv[1])
fin.write('%d\n' % line)
for i in range(0, line):
    a = random.randrange(1, MAX)
    b = random.randrange(1, MAX)
    c = a*b
    fin.write('%d %d\n' % (a, b))
    fout.write('%d\n' % c)
fin.close()
fout.close()
