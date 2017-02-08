#!python
# Round 1A 2016 - The Last Word
# https://code.google.com/codejam/contest/4304486/dashboard

import math
import sys
from collections import deque

debug_enabled = False
f = sys.stdin

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

T = int(f.readline())

for t in range(1, T+1):
    word = f.readline().strip()
    
    lastWord = deque([word[0]], len(word))
    
    for i in range(1, len(word)):
        if word[i] >= lastWord[0]:
            lastWord.appendleft(word[i])
        else:
            lastWord.append(word[i])
    result = ''.join(lastWord)       
    print ('Case #%d: %s') % (t, result)        
    
 
    
