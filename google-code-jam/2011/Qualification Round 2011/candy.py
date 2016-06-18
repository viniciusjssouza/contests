##############################################################
# C - Candy Splitting - Google Code Jam - Qualification Round 2011
# Autor: Vinicius J. S. Souza
# Data: 15/02/2012
# Tecnicas: math - exclusive-or operations.
##############################################################
from sys import stdin

debug = True

T = int(stdin.readline())
for t in range(T) :
	N = int(stdin.readline())
	tmp = stdin.readline().strip().split(" ")
	min = 10e6
	sum = 0
	xor = 0
	for i in range(len(tmp)):
		val = int(tmp[i])
		if val < min :
			min = val
		sum += val		
		xor = val if xor == 0 else (xor ^ val)		
	if xor == 0:
		print("Case #%d: %d" % (t+1,sum-min))	
	else:
		print("Case #%d: NO" % (t+1))	
	