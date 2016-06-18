/******************************************************************
* ACM - North America - East Central 2006 - Snakes on the plane
*
* Autor: Vinicius J. S. Souza 
* Data: 10/08/2010
* Tecnicas: flood fill, connected components
* Dificuldade(1-10): 6
* Complexidade: O(n^2)
*********************************************************************/
#include<cstdio>
#include<iostream>
#include<string.h>

using namespace std;

int N, M, nEnds;
char grid[205][205];
bool used[205][205];
bool ok;

int getGrau(int i, int k) {
	int grau = 0;
	if (k + 1 < M && grid[i][k+1] == '1')
		grau++;
	if (i-1 >= 0 && grid[i-1][k] == '1')
		grau++;
	if (k-1 >= 0 && grid[i][k-1] == '1')
		grau++;
	if (i+1 < N && grid[i+1][k] == '1')
		grau++;
	return grau;
}

bool noWay(int i, int k) {
	if (k+1 < M && grid[i][k+1] == '0' && getGrau(i, k+1) <= 1)
		return false;
	if (i-1 >= 0 && grid[i-1][k] == '0' && getGrau(i-1, k) <= 1)
		return false;
	if (k-1 >= 0 && grid[i][k-1] == '0' && getGrau(i, k-1) <= 1)
		return false;
	if (i+1 < N && grid[i+1][k] == '0' && getGrau(i+1, k) <= 1)
		return false;
	return true;
}

void isMaxSnake(int i, int k) {
	used[i][k] = true;
	int grau = getGrau(i,k);
	if (grau == 0) {
		if (noWay(i, k) == false) 
			ok = false;
		else 
			nEnds += 2;
	} else if (grau == 1) {
		nEnds++;
		if (noWay(i,k) == false) 
			ok = false;
	} else if (grau >= 2) {
		if (grau > 2) 
			ok= false;
	}		
	if (k + 1 < M && !used[i][k+1] && grid[i][k+1] == '1')
		isMaxSnake(i, k+1);
	if (i-1 >= 0 && !used[i-1][k] && grid[i-1][k] == '1')
		isMaxSnake(i-1, k);
	if (k-1 >= 0 && !used[i][k-1] && grid[i][k-1] == '1')
		isMaxSnake(i, k-1);
	if (i+1 < N && !used[i+1][k] && grid[i+1][k] == '1')
		isMaxSnake(i+1, k);
}

int main() {
	while (true) {
		scanf("%d %d", &N, &M);
		if (!N && !M)
			break;
		memset(used, false, sizeof(used));
		for (int i = 0; i < N; i++) 
			scanf("%s", grid[i]);			
		int conta = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < M; k++) {
				if (!used[i][k] && grid[i][k] == '1') {
					nEnds = 0;
					ok = true;
					isMaxSnake(i, k);
					if (ok && nEnds == 2) 
						conta++;
				}		
			}
		}	
		printf("%d\n", conta);		
	}
	return 0;
} 
