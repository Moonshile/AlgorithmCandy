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
MAX = 100;
N = 10
K = 10
fin.write('%d\n' % N)
for i in range(0, N):
    x = random.randrange(1, MAX)
    y = random.randrange(1, MAX)
    fin.write('%d %d\n'%(x, y))
fin.write('%d\n' % K)
for i in range(0, K):
    x = random.randrange(1, MAX)
    y = random.randrange(1, MAX)
    z = random.randrange(1, MAX)
    w = random.randrange(1, MAX)
    fin.write('%d %d %d %d\n' % (x, y, z, w))
fin.close()
