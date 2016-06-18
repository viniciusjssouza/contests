##############################################################
# Google Code Jam - Qualification Round 2011
# Autor: Vinicius J. S. Souza
# Data: 15/02/2012
# Tecnicas: ad-hoc. Uso de mapas/vetores
##############################################################
import sys

debug = True

def put(map, i, k, val) : 
	if (i in map) == False :
		map[i] = {}
	
	if (k in map[i]) == False :
		map[i][k] = val

T = int(sys.stdin.readline())
for i in range(T):
	line = sys.stdin.readline().split(" ")
	#if debug : print(line)
	C = int(line[0])
	ptr = 1
	comb = {}
	opp = {}
	for k in range(C) :
		tmp = line[ptr]
		put(comb, tmp[0], tmp[1], tmp[2])
		put(comb, tmp[1], tmp[0], tmp[2])
		ptr = ptr + 1
	D = int(line[ptr])
	ptr = ptr+1
	for k in range(D) :
		tmp = line[ptr]
		put(opp, tmp[0], tmp[1], True)
		put(opp, tmp[1], tmp[0], True)
		ptr = ptr + 1
	
	elements = line[ptr+1].strip()
	result = [];
	result.append(elements[0])
	for e in range(1, len(elements)) :
		curr = elements[e]
		
		if len(result) == 0 :
			result.append(curr)
			continue
		lastR = result[len(result)-1]
		
		if (lastR in comb) and (curr in comb[lastR]) :
			result[len(result)-1 : len(result)] = comb[lastR][curr]
		else :
			cleared = False
			for e2 in range(len(result)) :
				if (result[e2] in opp) and (curr in opp[result[e2]]) :
					result = []
					cleared = True
					break
			if cleared == False :
				result.append(curr)
	print("Case #%d: [" % (i+1), end = '')			
	for e in range(len(result)):
		if e > 0 :
			print(', ', end='')
		print (result[e], end='')
	print("]")
	
