#!python
# Round 1A 2016 - Rank and File
# https://code.google.com/codejam/contest/4304486/dashboard

import math
import sys

debug_enabled = False
f = sys.stdin

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

T = int(f.readline())

for t in range(1, T+1):
    N = int(f.readline())
    count = dict()
    for n in range(0, 2*N-1):
        line = f.readline().strip()
        row = map(lambda x: int(x), line.split())    
        for h in row:
            curr = count.get(h, 0)
            count[h] = curr+1            
    result = []
    for h, total in count.iteritems():
        if total % 2 == 1:
            result = result + [h]
    result.sort()
    print ('Case #%d: %s') % (t, ''.join(str(e)+' '  for e in result))        
    
 
    
