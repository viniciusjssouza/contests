/***************************************************************
* Dominó - Seletiva IOI 2002
*
* Autor: Vinicius J. S. Souza
* Data: 14/07/2010
* Tecnicas: backtracking
* Dificuldade: 5
******************************************************************/

#include<iostream>
#include<cstdio>
#include<vector>

#define USED  -1;

using namespace std;

typedef pair<int,int> pii;

int M[7][8];
int nconfig = 0;
int pcs[28][2] = {
	0,0, 0,1, 0,2, 0,3, 0,4, 0,5, 0,6,
	1,1, 1,2, 1,3, 1,4, 1,5, 1,6,
	2,2, 2,3, 2,4, 2,5, 2,6,
	3,3, 3,4, 3,5, 3,6,
	4,4, 4,5, 4,6, 
	5,5, 5,6,
	6,6
};
vector<vector<pii> > memo(28);

void backtrack(int pos) {
	int a = pcs[pos][0], b = pcs[pos][1];
	for (int c = 0; c < memo[pos].size(); c++) {
		int i = memo[pos][c].first, k = memo[pos][c].second;
		if (k+1 < 8 && ((M[i][k] == a && M[i][k+1] == b) || 
			(M[i][k] == b && M[i][k+1] == a))) {
			int ant1 = M[i][k], ant2 = M[i][k+1];
			M[i][k] = M[i][k+1] = USED;
			if (pos >= 27)
				nconfig++;
			else 
				backtrack(pos+1);
			M[i][k] = ant1;
			M[i][k+1] = ant2;
		}
		if (i+1 < 7 && ((M[i][k] == a && M[i+1][k] == b) || 
			(M[i][k] == b && M[i+1][k] == a))) {
			int ant1 = M[i][k], ant2 = M[i+1][k];
			M[i][k] = M[i+1][k] = USED;
			if (pos >= 27)
				nconfig++;
			else 
				backtrack(pos+1);
			M[i][k] = ant1;
			M[i+1][k] = ant2;					
		}		
	}	
}

int main() {
	int N;
	scanf("%d", &N);
	for (int tcase=1; tcase <= N; tcase++) {
		for (int i = 0; i < 7; i++) {
			for (int k = 0; k < 8; k++)
				scanf("%d", &M[i][k]);
		}
		for (int p = 0; p < 28; p++) {
			memo[p].clear();
			int a = pcs[p][0], b = pcs[p][1];
			for (int i = 0; i < 7; i++) {
				for (int k = 0; k < 8; k++) {
					if (k+1 < 8 && ((M[i][k] == a && M[i][k+1] == b) || 
						(M[i][k] == b && M[i][k+1] == a))) 
							memo[p].push_back(pii(i,k));
					else if (i+1 < 7 && ((M[i][k] == a && M[i+1][k] == b) || 
						(M[i][k] == b && M[i+1][k] == a))) {
							memo[p].push_back(pii(i,k));
					}		
				}	
			}		
		}
		nconfig = 0;
		backtrack(0);
		printf("Teste %d\n%d\n\n", tcase, nconfig);		
	}
	
	return 0;
} 
