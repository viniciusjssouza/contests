#!python
# Round 1B 2016 - Close Match
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
UNKNOWN = '?'
coders = jammers = None

def calcScore(current, digit, place):
    return current + int(math.pow(10, place)) * int(digit)

def tryScore(i, scoreC, scoreJ, digits):
    debug('tryScore at %d: (%d, %d) - try: %s', i, scoreC, scoreJ, str(digits))

    digitC, digitJ = digits
    scoreC = calcScore(scoreC, digitC, len(coders)-1-i) 
    scoreJ = calcScore(scoreJ, digitJ, len(coders)-1-i)
    return findMin(i+1, scoreC, scoreJ)

def minDiff(options):
    minD = 99999999999999999999
    result = None
    for score in options:
        if abs(score[0]-score[1]) < minD:
            result = score;
            minD = abs(score[0]-score[1])
    return result
    
def findMin(i, scoreC, scoreJ):
    global coders, jammers
    if i >= len(coders):
        return [scoreC, scoreJ]
        
    if coders[i] == UNKNOWN and jammers[i] == UNKNOWN:
        debug('? ?')
        if scoreC > scoreJ:
            score = tryScore(i, scoreC, scoreJ, [0,9])
        elif scoreC < scoreJ:
            score = tryScore(i, scoreC, scoreJ, [9,0])
        else:
            a = tryScore(i, scoreC, scoreJ, [0,0])
            b = tryScore(i, scoreC, scoreJ, [0,1])
            c = tryScore(i, scoreC, scoreJ, [1,0])
            score = minDiff([a,b,c])              
            
    elif coders[i] == UNKNOWN and jammers[i] != UNKNOWN:    
        debug('? N')
        if scoreC > scoreJ:
            score = tryScore(i, scoreC, scoreJ, [0, int(jammers[i])])
        elif scoreC < scoreJ:
            score = tryScore(i, scoreC, scoreJ, [9, int(jammers[i])])
        else:
            options = []
            N = int(jammers[i])            
            if N > 0:
                options.append(tryScore(i, scoreC, scoreJ, [N-1,N]))
            options.append(tryScore(i, scoreC, scoreJ, [N,N]))    
            if N < 9:
                options.append(tryScore(i, scoreC, scoreJ, [N+1,N]))
            score = minDiff(options)              
            
    elif coders[i] != UNKNOWN and jammers[i] == UNKNOWN:        
        debug('N ?')
        if scoreC > scoreJ:
            score = tryScore(i, scoreC, scoreJ, [int(coders[i]), 9])
        elif scoreC < scoreJ:
            score = tryScore(i, scoreC, scoreJ, [int(coders[i]), 0])
        else:
            options = []
            N = int(coders[i])            
            if N > 0:
                options.append(tryScore(i, scoreC, scoreJ, [N,N-1]))
            options.append(tryScore(i, scoreC, scoreJ, [N,N]))    
            if N < 9:
                options.append(tryScore(i, scoreC, scoreJ, [N,N+1]))
            score = minDiff(options) 
    else:
        debug('N N')
        score = tryScore(i, scoreC, scoreJ, [int(coders[i]), int(jammers[i])])
    return score

def fillZeros(n):
    x = str(n)
    while len(x) < len(coders):
       x = '0' + x
    return x
    
for t in range(1, T+1):
    coders, jammers = f.readline().strip().split()
    scoreC, scoreJ = findMin(0, 0, 0)        
            
    print ('Case #%d: %s %s') % (t, fillZeros(scoreC), fillZeros(scoreJ))        
    
 
    
