#!/usr/bin/python

import os, random, sys

infile = ''
for i in range(1, 100):
    if os.path.exists('zau-%d.in'%i):
        continue
    infile = 'zau-%d.in'%i
    break

ifl = open(infile, 'w')
H = 100
N = 1000
M = 101
STEP = 0.01
if len(sys.argv) == 5:
    H = int(sys.argv[1])
    N = int(sys.argv[2])
    M = int(sys.argv[3]) + 1
    STEP = float(sys.argv[4])
ifl.write('%d %d\n'%(N, H))
for i in range(0, N):
    h = random.randrange(0, H + 1)
    s = random.choice('+-')
    ifl.write('%d %c\n'%(h, s))
ifl.write('%d\n'%(M*M))
for i in range(0, M):
    for j in range(0, M):
        ifl.write('%.6f %.6f\n'%(STEP*i, STEP*j))
ifl.close()
