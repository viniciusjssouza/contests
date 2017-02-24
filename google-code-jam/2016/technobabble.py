#!python
# Round 1B 2016 - Tecnobable
# https://code.google.com/codejam/contest/11254486/dashboard
#

import math
import sys

debug_enabled = False
f = sys.stdin
sys.setrecursionlimit(10000)

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

T = int(f.readline())

for t in range(1, T+1):
    N = int(f.readline())
    
    words1 = set()
    words2 = set()
    count = 0
    for n in range(0, N):
        a,b = f.readline().split()
        if a in words1 and b in words2:
            count = count + 1
        else:
            words1.add(a)        
            words2.add(b)
    print ('Case #%d: %d') % (t, count)        
    
 
    
