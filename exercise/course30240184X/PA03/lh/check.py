#!/usr/bin/python

import sys

f1 = open(sys.argv[1])
f2 = open(sys.argv[2])
lines1 = f1.readlines()
lines2 = f2.readlines()
for i in range(0, len(lines1)):
    if lines1[i].strip() == lines2[i].strip():
        continue
    print i
f1.close()
f2.close()
