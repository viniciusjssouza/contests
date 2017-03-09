#!python
# Round 1B 2016 - Tecnobable
# https://code.google.com/codejam/contest/11254486/dashboard#s=p2
# 
# Consider the words as a bipartite graph and apply a max matching algorithm.
# The edges/words included in the max matching are surely not fake. 

import math
import sys
from graphs import *

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
    graph = Graph()
    
    for n in range(0, N):
        a,b = f.readline().split()
        graph.connect(a + "_U", b + "_V")
        
    matches = MaxMatching(graph)    
    count = matches.size()
    
    for w in graph.vertexes():
        if w not in matches.matches:
            count = count + 1
            
    print ('Case #%d: %d') % (t, N-count)        
    
 
    
