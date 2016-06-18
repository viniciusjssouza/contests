/*******************************************************
* UVa 102 - Ecologial Bin Packing
*
* Autor: Vinicius J. S. Souza
* Data: 06/01/2011
* Tecnicas: backtracking
********************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i,N) for(int i = 0; i < N; i++)

#define INF 0x1fffffff

using namespace std;

int data[9];
map<char, bool> used;
char bins[] = {'B', 'C', 'G'}, resp[3], aux[3];
int minimo;

int calculTrocas(int pos, char c) {
	if (pos == 0){
		if (c == 'B')
			return data[3] + data[6];
		else if (c == 'C')
			return data[5] + data[8];
		else
			return data[4] + data[7];
	} else if (pos == 1) {
		if (c == 'B')
			return data[0] + data[6];
		else if (c == 'C')
			return data[2] + data[8];
		else
			return data[1] + data[7];

	} else if (pos == 2) {
		if (c == 'B')
			return data[3] + data[0];
		else if (c == 'C')
			return data[5] + data[2];
		else
			return data[4] + data[1];

	}
	return INF;
}

void backtrack(int nivel, int trocas){
	if (nivel == 3 && trocas < minimo){
		minimo = trocas;
		memcpy(resp, aux, sizeof(aux));
		return;
	}
	para(i, 3) {
		if (used[bins[i]] == false) {
			int t = calculTrocas(nivel, bins[i]);
			if (t < minimo) {
				used[bins[i]] = true;
				aux[nivel] = bins[i];
				backtrack(nivel+1, trocas+t);
				used[bins[i]] = false;				
			}
				
		}
	}
}

int main() {
	while (!feof(stdin) && scanf("%d", &data[0]) == 1) 
	{
		for (int i= 1; i < 9; i++) {
			scanf("%d", &data[i]);	
		}
		minimo = INF;
		used.clear();
		backtrack(0, 0);
		printf("%c%c%c %d\n", resp[0], resp[1], resp[2], minimo);
	}
	return 0;
}
