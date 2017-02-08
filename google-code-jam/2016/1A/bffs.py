#!python
# Round 1A 2016 - BFFs
# https://code.google.com/codejam/contest/4304486/dashboard
#
# Here, two cases must be considered:
#     1) Find all the cycles. Take the length of the longest one.
#     2) For cycles of length 2, find the length of the largest connected component
#       for each one of the two kids plus the number of elements involved on cycles with length 2 
#        and connected component with length 2.
#     In the end, take, the longest circle from 1) and 2).  
#  

import math
import sys
import pdb
import sys
from collections import deque

debug_enabled = False
f = sys.stdin
sys.setrecursionlimit(10000)

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

def cycleLength(current, to, parent):
    return 1 if current == to or parent[current] == None else cycleLength(parent[current], to, parent) + 1
  
def dfs(bffs, inverseBffs, kid, parent, visited = set()):
    visited.add(kid)
    bf = bffs[kid]    
    maxCircle = 0
    
    if bf not in visited:
        parent[bf] = kid
        maxCircle = dfs(bffs, inverseBffs, bf, parent, visited)
    else:
        length = cycleLength(kid, bf, parent)
        if length > 2:            
            maxCircle = length
            
    visited.remove(kid)        
    return maxCircle    
    
def findLongestCycle(bffs, inverseBffs):
    parent = dict.fromkeys(range(1, len(bffs)))
    maxCount = 0
    for kid in range(1, len(bffs)):
        debug('visiting kid: %d', kid)
        count = dfs(bffs, inverseBffs, kid, parent)             
        maxCount = max(maxCount, count)
        debug('maxcount: %d', maxCount)
    return maxCount
    
def inverse(bffs):
    inverseBffs = dict()
    for i in range(1, len(bffs)):
        inverseBffs[i] = []
    for i,k in enumerate(bffs):
        if i > 0: # skip position 0
            inverseBffs[k].append(i) 
    return inverseBffs
    
def greatestComponent(inverseBffs, v, visited):
    visited.add(v)
    count = 0
    for w in inverseBffs[v]:
        if w not in visited:
            ccLen = greatestComponent(inverseBffs, w, visited)            
            count = max(count, ccLen)
    debug('Component length for %d: %d', v, count+1)        
    return count + 1       
    
def computePairs(bffs, inverseBffs):
    pairsCount = 0
    accounted = set()
    for kid in range(1, len(bffs)):
        bf = bffs[kid]
        if kid == bffs[bf] and kid not in accounted:
            accounted.add(bf)
            pairsCount = pairsCount + greatestComponent(inverseBffs, kid, set([bf]))
            pairsCount = pairsCount + greatestComponent(inverseBffs, bf, set([kid]))                             
    return pairsCount        

# main    
T = int(f.readline())
for t in range(1, T+1):
    N = int(f.readline())
    bffs =  [None] + map(lambda x: int(x), f.readline().split())
    
    inverseBffs = inverse(bffs)
    pairsCount = computePairs(bffs, inverseBffs)    
    debug('Pairs counts: %d', pairsCount)
    maxCycle = findLongestCycle(bffs, inverseBffs) 
    print ('Case #%d: %d') % (t, max(maxCycle, pairsCount))        
