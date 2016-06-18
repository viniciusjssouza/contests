/**********************************************************
* Make it Smooth - Google Code Jam 2010 - Round 1A
*
* Autor: Vinicius J. S. Souza
* Data: 04/08/2010
* Tecnicas: dp + memoization
* Dificuldade(1-10): 8
* Complexidade: O(256*256*N);
**********************************************************/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>

#define NULO -1
#define VAZIO 256

using namespace std;

int D, I, M, N, T;
int data[110], memo[110][260];

int backtrack(int nivel, int prev) {
	if (nivel < 0)
		return 0;
	if (memo[nivel][prev] != NULO)
		return memo[nivel][prev];
		
	int best = 0x3fffffff;
	// custo para mover e inserir
	for (int i = 0; i < 256; i++) {
		int partial_sol = backtrack(nivel-1, i);
		int move_cost = abs(data[nivel] - i);
		int insert_cost;
		if (prev == VAZIO)
			insert_cost = 0;
		else {
			int dist = abs(i-prev);
			insert_cost = (dist == 0? 0 : (M == 0 ? 1000000 :(ceil((float)dist / (float)M)-1)*I));	
		}
		best = min(best, partial_sol + move_cost + insert_cost);
	}
	// custo para deletar		
	best = min(best, backtrack(nivel-1, prev) + D);

	return (memo[nivel][prev] = best);	
}


int main() {
	scanf("%d", &T);
	for (int tcase = 1; tcase <= T; tcase++) {
		scanf("%d %d %d %d", &D, &I, &M, &N);
		memset(memo, NULO, sizeof(memo));
		for (int i = 0; i < N; i++) {
			scanf("%d", &data[i]);			
		}
		printf("Case #%d: %d\n", tcase, backtrack(N-1, VAZIO));
	}
	return 0;
} 
