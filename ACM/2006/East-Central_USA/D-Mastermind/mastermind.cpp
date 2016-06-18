/**********************************************************
* D - Mastermind - ACM - North America - East-Central 2006
*
* Autor: Vinicius J. S. Souza
* Data: 18/08/2010
* Tecnicas: Forca bruta
* Dificuldade(1-10): 7
***********************************************************/

#include<cstdio>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

#define INF 0x3fffffff

int L, C, N;
char guesses[10][16], p[33000][16], sol[1600][16];
char cores[] = {"ABCDEFGHIJKLMNOPQRSTUVX"};
char temp[16];
int pSz, solSz, best;
int bw[10][2], bwCount[16][16];
bool used[2][16];

void findPoss(int nivel) {
	if (nivel >= L) {
		temp[nivel] = '\0';
		strcpy(p[pSz], temp);
		pSz++;	
		return;
	}
	for (int i = 0; i < C; i++) {
		temp[nivel] = cores[i];
		findPoss(nivel+1);
	}		
}

void blackWhite(char guess[], char sol[], int &b, int &w) {
	b = w = 0;
	memset(used, false, sizeof(used));
	for (int k = 0; k < L; k++) {
		if (guess[k] == sol[k]) {
			used[0][k] = used[1][k] = true;
			b++;			
		}
	}
	for (int k = 0; k < L; k++) {
		if (used[0][k] == false) {
			for (int m = 0; m < L; m++) {
				if (used[1][m] == false && guess[k] == sol[m]) {
					used[0][k] = used[1][m] = true;
					w++;
					break;
				}
			}
		}
	}
}

bool ok(char str[]) {
	for (int i = 0; i < N; i++) {
		int b,w;
		blackWhite(guesses[i], str, b, w);
		if (b != bw[i][0] || w != bw[i][1])
			return false;
	}
	return true;
}

int solve() {
	int solIdx = 0;
	for (int i = 0; i < pSz; i++) {
		int maxV = -1;
		memset(bwCount, 0, sizeof(bwCount));
		for (int s = 0; s < solSz; s++) {
			int b,w;
			blackWhite(p[i], sol[s], b, w);
			if (b < L) 
				bwCount[b][w]++;
			if (bwCount[b][w] > maxV)
				maxV = bwCount[b][w];										
		}
		if (maxV < best) {
			best = maxV;
			solIdx = i;
		}
	}
	return solIdx;
}

int main() {
	int ncase;
	scanf("%d", &ncase);
	while (ncase--) {
		scanf("%d %d %d", &L, &C, &N);
		for (int i = 0; i < N; i++) {
			scanf("%s %d %d", guesses[i], &bw[i][0], &bw[i][1]);			
		}		
		pSz = 0;
		findPoss(0);
		solSz = 0;
		for (int i = 0; i < pSz; i++) {
			if (ok(p[i])) {
				strcpy(sol[solSz++], p[i]);				
			}
		}
		best = INF;
		int idx = solve();
		printf("%s %d\n", p[idx], best);		
	}
	return 0;
} 
