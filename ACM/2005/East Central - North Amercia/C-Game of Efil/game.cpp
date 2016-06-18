/******************************************************************
* C - Game of Efil - North America - East Central - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 21/08/2010
* Tecnicas: busca recursiva (espaço de busca de, no maximo, 2^16
* Dificuldade(1-10): 6
********************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int M, N, K;
bool final[17][17], temp[17][17], cpy[17][17];
int conta;

bool isValid() {
	for (int i = 0; i < M; i++) {
		for (int k = 0; k < N; k++) {
			int leste = (k+1 >= N) ? 0 : k+1;
			int norte = (i-1 < 0) ? M-1 : i-1;
			int oeste = (k-1 < 0) ? N-1 : k-1;
			int sul   = (i+1 >= M) ? 0 : i+1;
			int vcount = 0;
			if (temp[i][leste]) // leste
				vcount++;
			if (temp[norte][leste]) // nordeste
				vcount++;
			if (temp[norte][k]) // norte
				vcount++;
			if (temp[norte][oeste]) // noroeste
				vcount++;
			if (temp[i][oeste]) // oeste
				vcount++;
			if (temp[sul][oeste]) // sudoeste
				vcount++;
			if (temp[sul][k]) // sul
				vcount++;
			if (temp[sul][leste]) // sudeste
				vcount++;	
			if (temp[i][k]) {
				if (vcount <= 1 || vcount >= 4)
					cpy[i][k] = false;					
			} else {
				if (vcount == 3)
					cpy[i][k] = true;
			}		
		}
	}
	for (int i = 0; i < M; i++) {
		for (int k = 0; k < N; k++) {
			if (cpy[i][k] != final[i][k])
				return false;
		}
	}
	return true;
}

void solve(int lin, int col) {
	if (lin >= M) {
		memcpy(cpy, temp, sizeof(temp));			
		if (isValid()) {
			conta++;
		}
		return;
	}
	int nextLin = (col+1 >= N) ? lin+1 : lin;
	int nextCol = (col+1 >= N) ? 0 : col+1; 
	temp[lin][col] = true;
	solve(nextLin, nextCol);
	temp[lin][col] = false;
	solve(nextLin, nextCol);
}

int main() {
	int tcase = 1;
	while(true) {
		scanf("%d %d", &M, &N);
		if (!N && !M)
			break;
		scanf("%d", &K);
		memset(final, false, sizeof(final));
		for (int k = 0; k < K; k++) {
			int r, c;
			scanf("%d %d", &r, &c);	
			final[r][c] = true;
		}
		memset(temp, false, sizeof(temp));
		conta = 0;
		solve(0,0);
		if (conta > 0)
			printf("Case %d: %d possible ancestors.\n", tcase++, conta);
		else
			printf("Case %d: Garden of Eden.\n", tcase++);
	}
	return 0;
}
 
