/************************************************************************
* H - Two Ends - East Central - North America - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 09/06/2010
* Tecnicas: programacao dinamica + memoization
********************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

#define INF 0x3fffffff

using namespace std; 

int memo[1001][1001], data[1001];
int N;

int backtrack(int inf, int sup) {
	if (memo[inf][sup] != 0) 
		return memo[inf][sup];
	if (sup-inf == 2) {
		return max(data[inf]-data[sup-1], data[sup-1]-data[inf]);
	} 
	int best = -INF;
	if (data[inf+1] >= data[sup-1]) {
		int temp = (data[inf] - data[inf+1]);
		best = max(backtrack(inf+2, sup)+ temp, best);
	} else {
		int temp =  (data[inf] - data[sup-1]);
		best = max(backtrack(inf+1, sup-1) + temp, best);
	}
	if (data[inf] >= data[sup-2]) {
		int temp =  (data[sup-1] - data[inf]);
		best = max(backtrack(inf+1, sup-1)+temp, best);
	} else {
		int temp = (data[sup-1] - data[sup-2]);
		best = max(backtrack(inf, sup-2)+temp, best);
	}	
	return (memo[inf][sup] = best);
}

int main() {
	int tcase = 1;
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			scanf("%d", &data[i]);
		}
		memset(memo, 0, sizeof(memo)); 
		int best = backtrack(0, N);
		printf("In game %d, the greedy strategy might lose by as many as %d points.\n",
			tcase++, best);
	}	
	return 0;
}
