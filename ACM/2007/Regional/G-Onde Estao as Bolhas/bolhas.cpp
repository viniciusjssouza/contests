/******************************************************************************
 * ACM - Onde Estao as Bolhas - Regional de 2007
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 24/05/2010
 * Tecnicas: arvore binaria de busca (set)
 * Dificuldade: 7 (1-10)
 **********************************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<set>

using namespace std;

int vet[100010];

int main()
{
	int N, T, pos;
	while (true)
	{
		scanf("%d %d", &N, &T);
		if (!N && !T) break;
		set<int> nused;
		for (int i = 0; i <= N; i++) {
			nused.insert(i);
			vet[i-1] = -1;
		}
		int i = 1;		
		for (; i <= T; i++) {
			scanf("%d", &pos);
			if (vet[pos] >= 0) {
				pos = (*nused.upper_bound(pos));
			} 
			vet[pos] = i;
			nused.erase(nused.find(pos));	
		}
		set<int>::iterator it = nused.begin();
		for (; i <= N && it != nused.end(); i++, it++) {
			vet[*it] = i;						
		} 
		for (int i = 0; i < N; i++) {
			printf("%d ", vet[i]);
		} 
		putchar('\n');
	}
	return 0;
}

