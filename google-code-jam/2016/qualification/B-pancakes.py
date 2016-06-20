#!python
# Qualification Round 2016 - Revenge of Pancakes
# https://code.google.com/codejam/contest/6254486/dashboard#s=p1

import math
import sys
from collections import deque

debug_enabled = False
f = sys.stdin

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

def flip(stack, index):
    for i in range(0,index):
        pos = (1 << i)
        if (stack & pos == 0):
            stack = stack | pos
        else:
            stack -= pos
    return stack    

def bfs(stack):
    global visited

    queue = deque([stack])
    visited[stack] = 0
    
    while queue: # while the queue is not empty
        current = queue.popleft()
        count = visited[current]
        
        allFlipped = long((1 << N)-1)
        if current == allFlipped:            
            return visited[current]

        bit0 = current & 1       
        i = 1
        while i < N and (current >> i) & 1 == bit0:
            i = i+1
        debug("stack: %d bit0: %d i: %d", current, bit0,i)
            
        nextFlip = flip(current, i)
        if (not nextFlip in visited):
           queue.append(nextFlip)
           visited[nextFlip] = count+1
    return -1   


T = int(f.readline())

for t in range(1, T+1):
    stackStr = f.readline().strip()
    stack = long(0)

    N = len(stackStr)

    # convert the string to a single number
    for i in range(len(stackStr)-1, -1, -1):
        stack = stack | (0 if stackStr[i] == '-' else (1 << i))

    #print stack
        
    #call the recursive function
    visited = dict()
    result = bfs(stack)
    print("Case #%d: %d" % (t, result))



    

    
 
    
