/***********************************************************************
* Brothers - ACM 2009 - Final sul-americana
*
* Autor: Vinicius J. S. Souza
* Data: 04/10/2010
* Tecnicas: forca bruta O(n³)
* Dificuldade: 5
************************************************************************/

#include<iostream>
#include<string.h>
#include<cstdio>

using namespace std;

int R,C,N, B;
int M[2][105][105];

int main() {
	while (true) {
		scanf("%d %d %d %d", &N, &R, &C, &B);
		if (!N && !R && !C && !B)
			break;
		for (int i = 0; i < R; i++) {
			for (int k = 0; k < C; k++) {
				scanf("%d", &M[0][i][k]);
				M[1][i][k] = M[0][i][k];
			}
		}
		for (int b = 0; b < B; b++) {
			for (int i = 0; i < R; i++) {
				for (int k = 0; k < C; k++) {
					if (k+1 < C && 
						(M[0][i][k+1] == M[0][i][k]+1 || (M[0][i][k+1] == 0 && M[0][i][k] == N-1))) {
						M[1][i][k+1] = M[0][i][k];
					}
					if (i-1 >= 0 && 
							(M[0][i-1][k] == M[0][i][k]+1 ||(M[0][i-1][k] == 0 && M[0][i][k] == N-1))) {
						M[1][i-1][k] = M[0][i][k];
					}
					if (k-1 >= 0 && (M[0][i][k-1] == M[0][i][k]+1 ||
							(M[0][i][k-1] == 0 && M[0][i][k] == N-1))) {
						M[1][i][k-1] = M[0][i][k];
					}
					if (i+1 < R && (M[0][i+1][k] == M[0][i][k]+1 ||
							(M[0][i+1][k] == 0 && M[0][i][k] == N-1))) {
						M[1][i+1][k] = M[0][i][k];
					}
				}
			}
			memcpy(M[0], M[1], sizeof(M[1]));
		}

		for (int i = 0; i < R; i++) {
			for (int k = 0; k < C; k++) {
				if (k)
					putchar(' ');
				printf("%d", M[1][i][k]);
			}
			putchar('\n');
		}
	}
	return 0;
}
