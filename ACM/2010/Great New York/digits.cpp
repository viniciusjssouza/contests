#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define para(i,B,N) for (int i = B; i < N; i++)

using namespace std;

typedef unsigned long long int int64;

int P;
const int MAXN = 64;
int64 tbl[MAXN+1][11];

int main() {
	para(i,0,10) {
		tbl[1][i] = 1;
	}
	tbl[1][10] = 10;

	para(i,2,MAXN+1) {
		tbl[i][0] = tbl[i][10] = 1;		
		para (k,1,10) {
			tbl[i][k] = tbl[i][k-1]+tbl[i-1][k];
			tbl[i][10] += tbl[i][k];
		}
	}

	scanf("%d", &P);
	para(i,0,P) {
		int N, x;
		scanf("%d %d", &x, &N);
		cout << x << " " << tbl[N][10] << endl;
	}	
	return 0;
}
