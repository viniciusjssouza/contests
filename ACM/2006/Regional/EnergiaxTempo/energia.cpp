/*******************************************************************
* Energia x Tempo - Maratona - Regional 2006
*
* Autor: Vinicius J. S. Souza
* Data: 15/03/2010
* Tecnicas: greedy - ad-hoc
* Dificuldade (1-10): 5
*******************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

typedef unsigned long long int64;

int nNiveis, nProgramas, eTroca, tTroca;
int64 edp[20][2];

int main() {
	while (true) {
		scanf("%d %d %d %d", &nNiveis, &nProgramas, &eTroca, &tTroca);
		if (!nNiveis && !nProgramas && !eTroca && !tTroca) break;
		int64 edpTroca = eTroca * tTroca;		
		int current, previous;
		for (int i = 0; i < nProgramas; i++) {
			current = (i & 1) ? 0 : 1;
			previous = (current) ? 0 : 1;
			for (int k = 0; k < nNiveis; k++) {
				int e, t;
				scanf("%d %d", &e, &t);
				edp[k][current] = e*t;
			}
			if (i) {
				for (int m = 0; m < nNiveis; m++) {
					int temp = edp[m][current];
					edp[m][current] += (edp[m][previous]);
					for (int k = 0; k < nNiveis; k++) {
						int troca = (m == k) ? 0 : edpTroca;
						edp[m][current] = min(edp[m][current], 
							(edp[k][previous] + troca + temp));						
					}
				}
			} else {
				for (int k = 1; k < nNiveis; k++)
					edp[k][current] += edpTroca;
			}		
					

		}
		int64 result = edp[0][current];
		for (int i = 1; i < nNiveis; i++) {
			result = min(result, edp[i][current]);
		}
		printf("%llu\n", result);
	}	
	return 0;
}
