#!python
# Round 1B 2016 - Getting the digits
# https://code.google.com/codejam/contest/11254486/dashboard

import math
import sys

debug_enabled = True
f = sys.stdin

def debug(msg, *args):
    if debug_enabled:
        print(msg % (args))

T = int(f.readline())
seq = [[0,'Z', 'ZERO'], [2,'W','TWO'], [6,'X','SIX'], \
        [7,'S','SEVEN'], [5,'V','FIVE'], [4,'F','FOUR'], [3,'R','THREE'], [1,'O','ONE'], \
        [8,'H','EIGHT'], [9,'N','NINE']]

def removeChars(toRemove, charCount):
    for letter in toRemove:
        curr = charCount[letter]
        charCount[letter] = curr - 1
                
def getDigits(charCount, word):
    digits = []
    for tuple in seq:
        for letter in word:
            if tuple[1] == letter and charCount.get(letter, 0) > 0:
               digits.append(tuple[0])
               removeChars(tuple[2], charCount)        
    digits.sort()
    return digits            

for t in range(1, T+1):
    word = f.readline().strip()
    
    charCount = dict()
    for letter in word:
        count = charCount.setdefault(letter, 0)
        charCount[letter] = count + 1

    #print charCount
    
    digits = getDigits(charCount, word)    
    
    result = ''.join(map(lambda d: str(d), digits))       
    print ('Case #%d: %s') % (t, result)        
    
 
    
