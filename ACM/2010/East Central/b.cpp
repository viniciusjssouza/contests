/****************************************************************
* ACM - ECNA 2010 - Flip it!
*
* Autor: Vinícius J. S. Souza
* Data: 21/10/2011
* Tecnicas: estrutura de dados: pilhas. Simulação.
******************************************************************/
#include<cstdio>
#include<cstring>
#include<deque>
#include<iostream>

#define debug false
#define para(i,B,N)  for(int i = B; i < N; i++)

using namespace std;

int N, M;
deque<int> v[21][21];
char flips[100];
int main() {
	int ncase = 1;
	while(true) {
		scanf("%d %d", &N, &M);
		if (!N && !M)
			break;
		para(i,0,N)
			para (k,0,M)
				v[i][k].clear();
		para(i, 0, N) {
			para(k, 0, M) {
				int x;
				scanf("%d", &x);
				v[i][k].push_back(x);
			}
		}
		int nflips = N+M-2;
		if (nflips > 0)
			scanf("%s", flips);
		else
			flips[0] = '\0';
		
		if (debug)
			printf("Flips:%s\n", flips);
		
		int l=0, r = M-1, t=0, b=N-1;
		para (i, 0, nflips) {
			if (flips[i] == 'L') {
				for (int row = t; row <=  b; row++) {
					while (!v[row][l].empty()) {
						int first = v[row][l].back();
						v[row][l].pop_back();
						v[row][l+1].push_back(-first);
					}					
				}
				l++;
			} else if (flips[i] == 'R') {
				for (int row = t; row <=  b; row++) {
					while (!v[row][r].empty()) {
						int first = v[row][r].back();
						v[row][r].pop_back();
						v[row][r-1].push_back(-first);
					}					
				}
				r--;
			} else if (flips[i] == 'T') {
				for (int col = l; col <= r; col++) {
					while (!v[t][col].empty()) {
						int first = v[t][col].back();
						v[t][col].pop_back();
						v[t+1][col].push_back(-first);
					}					
				}
				t++;
			} else if (flips[i] == 'B'){
				for (int col = l; col <=  r; col++) {
					while (!v[b][col].empty()) {
						int first = v[b][col].back();
						v[b][col].pop_back();
						v[b-1][col].push_back(-first);
					}					
				}
				b--;
			} else {
				printf("ERRO!!! FLIP INVALIDO!!!\n");
			}
		}
		printf("Case %d:", ncase++, t, l);
		for (int i = 0; i < v[t][l].size(); i++) {
			if (v[t][l][i] > 0)
				printf(" %d", v[t][l][i]);
		}
		printf("\n");
	}
}