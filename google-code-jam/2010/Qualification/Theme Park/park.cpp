/*****************************************************************
* Theme Park - Google Code Jam 2010
*
* Autor: Vinicius J. S. Souza
* Data: 25/07/2010
* Tecnicas: reconhecimento de ciclos
* Dificuldade: 5
* Complexidade: O(N)
***************************************************************/
#include <cstdio>
#include <iostream>

#define NULO -1

using namespace std;

long long int grupos[1010], tab[1010][2];

int main() {
	int T, R, K, N;
	scanf("%d", &T);
	for (int tcase =1; tcase <= T; tcase++) {
		scanf("%d %d %d", &R, &K, &N);
		for (int i = 0; i < N; i++) {
			scanf("%lld", &grupos[i]);
		}
		memset(tab, NULO, sizeof(tab));
		int idx = 0;
		while (tab[idx][0] == NULO) {
			long long int i = idx, qnt = 0;
			bool cicle = 0;
			for ( ; qnt + grupos[i] <= K; i = (i+1) % N) {
				if (idx == i) {
					if (cicle)
						break;
					cicle =  true;
				}
				qnt += grupos[i];
			}
			tab[idx][0] = qnt;
			tab[idx][1] = i;	
			idx = i;
		}
		int bound = idx;
		long long int out = 0, in = 0, inLen = 1, outLen = 0;
		for (idx = 0; idx != bound; idx = tab[idx][1], outLen++) {
			out += tab[idx][0];
		}
		in += tab[bound][0];
		for (idx = tab[bound][1]; idx != bound; idx = tab[idx][1], inLen++) {
			in += tab[idx][0];			
		}
	 	R -= outLen;
		long long int total = out;
		total += (R / inLen) * in;
		long long int resto = R % inLen;
		for (int i = 0, idx = bound; i < resto; i++, idx = tab[idx][1])
			total += tab[idx][0];					
		printf("Case #%d: %lld\n", tcase, total);
						
	}
	return 0;
} 
