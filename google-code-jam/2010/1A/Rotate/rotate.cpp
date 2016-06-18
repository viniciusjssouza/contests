/******************************************************************
* Rotate - Google Code Jam 2010 - Round 1A
*
* Autor: Vinicius J. S. Souza
* Data: 28/07/2010
* Tecnicas: Grids
* Dificuldade(1-10): 5
* Complexidade: ~ O(N^2) - maior durante a aplicacao do efeito de gravidade 
**************************************************************/
#include<cstdio>
#include<iostream>

#define		ROW		0
#define		COL		1
#define		RGT		2
#define		LFT		3  

using namespace std;

char grid[55][55];
int tbl[55][55][4];
int K, N, T, tcase = 1;

void printGrid() {
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			printf("%c", grid[i][k]);
		}
		printf("\n");
	}
	printf("-----------------------\n");
}

int main() {
	for (scanf("%d", &T); tcase <= T; tcase++) {
		scanf("%d %d", &N, &K);
		for (int k = N-1; k >= 0; k--) {
			for (int i = 0; i < N; i++) {
				cin >> grid[i][k];
			}
		}
		//printGrid();
		// efeito da gravidade
		for (int i = N-2; i >= 0; i--) {
			for (int k = 0; k < N; k++) {
				if (grid[i][k] == '.')
					continue;
				for (int m = i+1; grid[m][k] == '.'; m++) {
					grid[m][k] = grid[m-1][k];
					grid[m-1][k] = '.';
				}
			}
		}
		//printGrid();
		// analisa condicao de vitoria
		for (int i = 0; i < N; i++)
			for (int k = 0; k < N; k++)
				tbl[i][k][ROW] = tbl[i][k][COL] = tbl[i][k][RGT] = tbl[i][k][LFT] = 1;
		bool blueWin = false, redWin = false;
		for (int i = N-1; i >= 0 && (!blueWin || !redWin); i--) {
			for (int k = 0; k < N && (!blueWin || !redWin); k++) {
				if (grid[i][k] == '.')
					continue;			
				//column
				if (i-1 >= 0 && grid[i][k] == grid[i-1][k]) {
					tbl[i-1][k][COL] = tbl[i][k][COL] + 1;
					//printf("inc col=%d para (%d %d)\n", tbl[i-1][k][COL], i, k);
					if (tbl[i-1][k][COL] >= K) {
						if (grid[i][k] == 'R')
							redWin = true;
						else if (grid[i][k] == 'B')
							blueWin = true;
					}	
				}
				//row
				if (k+1 < N && grid[i][k] == grid[i][k+1]) {
					tbl[i][k+1][ROW] = tbl[i][k][ROW] + 1;
					//printf("inc row=%d para (%d %d)\n", tbl[i][k+1][ROW], i, k);
					if (tbl[i][k+1][ROW] >= K) {
						if (grid[i][k] == 'R')
							redWin = true;
						else if (grid[i][k] == 'B')
							blueWin = true;
					}	
				}
				//diagonal esquerda
				if (i-1 >= 0 && k-1 >= 0 && grid[i][k] == grid[i-1][k-1]) {
					tbl[i-1][k-1][LFT] = tbl[i][k][LFT] + 1;
					//printf("inc left=%d para (%d %d)\n", tbl[i-1][k-1][LFT], i, k);
					if (tbl[i-1][k-1][LFT] >= K) {
						if (grid[i][k] == 'R')
							redWin = true;
						else if (grid[i][k] == 'B')
							blueWin = true;
					}	
				}
				//diagonal direita
				if (i-1 >= 0 && k+1 < N && grid[i][k] == grid[i-1][k+1]) {
					tbl[i-1][k+1][RGT] = tbl[i][k][RGT] + 1;
					//printf("inc right=%d para (%d %d)\n", tbl[i-1][k+1][RGT], i, k);
					if (tbl[i-1][k+1][RGT] >= K) {
						if (grid[i][k] == 'R')
							redWin = true;
						else if (grid[i][k] == 'B')
							blueWin = true;
					}	
				}					
			}			
		}
		printf("Case #%d: ", tcase);
		if (blueWin && redWin)
			printf("Both\n");
		else if (redWin)
			printf("Red\n");
		else if (blueWin)
			printf("Blue\n");
		else if (!blueWin && !redWin) 
			printf("Neither\n");
	}
	return 0;	
}

