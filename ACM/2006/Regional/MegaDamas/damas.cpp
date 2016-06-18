/*******************************************************************
* MegaDamas - Regional - Maratona 2006
*
* Autor: Vinicius J. S. Souza
* Data: 17/03/2010
* Tecnicas: dfs - backtracking
* Dificuldade (1-10): 6
****************************************************************/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<deque>
#include<algorithm>

using namespace std;

#define free 0
#define my   1
#define op   2

typedef pair<int, int> pii;

int N, M;
int grid[400][400];
bool visited[400][400];
deque<pii> jog;

int dfs(int lin, int col) {
	int mx = 0;
	// sup direita
	if (lin-2 >= 0 && col+2 < M && grid[lin-1][col+1] == op &&
		grid[lin-2][col+2] == free) {
		int nextLin = lin-2, nextCol = col+2;
		grid[lin-1][col+1] = free;
		int temp = dfs(nextLin, nextCol);
		mx = max(mx, temp+1);
		grid[lin-1][col+1] = op;
	}
	// sup esquerda
	if (lin-2 >= 0 && col-2 >= 0 && grid[lin-1][col-1] == op &&
		grid[lin-2][col-2] == free) {
		int nextLin = lin-2, nextCol = col-2;
		grid[lin-1][col-1] = free;
		int temp = dfs(nextLin, nextCol);
		mx = max(mx, temp+1);
		grid[lin-1][col-1] = op;
	}
	// inf esquerda
	if (lin+2 < N && col-2 >= 0 && grid[lin+1][col-1] == op &&
		grid[lin+2][col-2] == free) {
		int nextLin = lin+2, nextCol = col-2;
		grid[lin+1][col-1] = free;	
		int temp = dfs(nextLin, nextCol);
		mx = max(mx, temp+1);
		grid[lin+1][col-1] = op;
	}
	// inf direita
	if (lin+2 < N && col+2 < M && grid[lin+1][col+1] == op &&
		grid[lin+2][col+2] == free) {
		int nextLin = lin+2, nextCol = col+2;
		grid[lin+1][col+1] = free;
		int temp = dfs(nextLin, nextCol);
		mx = max(mx, temp+1);
		grid[lin+1][col+1] = op;		
	}
//	printf("result (%d %d) = %d\n", lin, col, mx);
	return mx;
}

int main() {
	while (true) {
		scanf("%d %d", &N, &M);
		if (!N && !M) break;
		for (int i = 0; i < N; i++)
			for (int k = 0; k < M; k++) {
				grid[i][k] = free;
				visited[i][k] = false;
			}
		jog.clear();
		bool init = true;		
		for (int i = N-1; i >= 0; i--) {
			for (int k = (init) ? 0 : 1; k < M; k+=2) {
				scanf("%d", &grid[i][k]);
				if (grid[i][k] == my)
					jog.push_back(pii(i,k));	
			}
			init = !init;
		}
		int size = jog.size();
		int mx = 0;
		for (int i = 0;i < size; i++) {
			grid[jog[i].first][jog[i].second] = free;
			int temp = dfs(jog[i].first, jog[i].second);
			mx = max(mx, temp);
			grid[jog[i].first][jog[i].second] = my;
		}
		printf("%d\n", mx);		
	}
	return 0;
}
