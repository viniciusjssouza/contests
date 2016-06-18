/**************************************************************************
* Circuito Bioquimico Digital - Maratona Regional 2006
*
* Autor: Vinicius J. S. Souza
* Data: 10/03/2010
* Tecnicas: ad-hoc
* Dificuldade (1-10): 3
************************************************************************/
#include<iostream>
#include<cstdio>

using namespace std;

int P, N, C;
int conta[1010];

int main() {
	while (true) {
		scanf("%d %d %d", &P, &N, &C);
		if (!P && !N && !C) break;
		for (int i = 0; i < P; i++)
			conta[i] = 0;
		int total = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < P; k++) {
				int x;
				scanf("%d", &x);
				if (x) {
					conta[k]++;
				} else {
					if (conta[k] >= C)
						total++;
					conta[k] = 0;
				}		
			}
		}
		for (int i = 0; i< P; i++)
			if (conta[i] >= C)
				total++;
		printf("%d\n", total);
	}
	return 0;
}
