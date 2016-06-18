/**********************************************************************
* Festa Junina - Seletiva IOI 2003
*
* Autor: Vinicius J. S. Souza
* Data: 18/07/2010
* Tecnicas: backtracking
********************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

int inimigos[25][25], N, maxN;


void backtrack(int v, vector<int> &comissao) {
	comissao.push_back(v);
	if (comissao.size() > maxN)
		maxN = comissao.size();
	if (comissao.size()+(N-v) > maxN) {		
		for (int i = v+1; i <= N; i++) {
			bool ok = true;
			for (int k = 0; k < comissao.size(); k++) {
				if (inimigos[comissao[k]][i]) {
					ok = false;
					break;		 
				}
			}
			if (ok)
				backtrack(i, comissao);
		}	
	}
	comissao.pop_back();
}

int main() {
	int tcase = 1;
	while(1) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++) {
			for (int k = i; k <= N; k++)
				inimigos[i][k] = inimigos[k][i] = false;
 		}
		int x = 0;
		maxN = 1;
		for (int i = 1; i <= N; i++) {
			do {
				scanf("%d", &x);
				inimigos[i][x] = inimigos[x][i] = true;	
			}while(x != 0);
		}
		vector<int> comissao;
		for (int i = 1; i <= N; i++) {
			backtrack(i, comissao);
		}
		printf("Teste %d\n%d\n\n", tcase++, maxN);
	}
	return 0;
} 
