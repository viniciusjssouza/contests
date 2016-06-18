/****************************************************************
* ACM 2010 - East Central USA - F - Pro-Test Voting
*
* Autor: Vinicius J. S. Souza
* Data: 28/10/2011
* Tecnicas: Programacao Dinamica (memoization)
***************************************************************/
#include<iostream>
#include<cstdio>
#include<deque>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false
#define trace(x...) 	if(debug)printf(x);
#define Ip	1
#define DELTA 2

using namespace std;

int M,N;
int money[101][101];
int prec[101][3];
int memo[101][101];

inline int calculVotes(int p, double m) {
	double fp = (double)prec[p][Ip] + ((double)m / (double)(10.1+m))*(double)prec[p][DELTA]; 
	double votes = (((fp/100.0) * (double)prec[p][0]));
	trace("Sem arredondamento: %lf\n", votes);
	int v = round(votes);
	trace("Arredondando: %d\n", v);
	return v;
}

int solve(int p, int resto) {
	trace("Em %d com %d\n", p, resto);
	if (p == N-1) {
		money[p][resto] = resto;
		memo[p][resto] = calculVotes(p, resto);
		trace("Votos para %d gasto %d: %d\n", p,resto,memo[p][resto]);
		return memo[p][resto];
	}
	
	
	int best = resto;
	int votes = 0;
	para(i,0,resto+1) {
		int partial = memo[p+1][i];
		if (partial < 0) {
			partial = solve(p+1, i);			
		}
		partial += calculVotes(p,resto-i);
		if (partial > votes) {
			trace("Melhorado... gasto: %d Votos:\n", resto-i, partial);
			votes = partial;
			best = resto-i; 
		}
	}
	memo[p][resto] = votes;
	money[p][resto] = best;	
	trace("Votos para %d gasto %d: %d\n", p, best, votes);		
	return votes;
}

int main()
{
	int ncase = 1;
	while (1) {
		scanf("%d %d", &M, &N);
		if (!M && !N)
			break;
		para(i,0,N) {
			scanf("%d %d %d", &prec[i][0], &prec[i][Ip], &prec[i][DELTA]);
		}
		memset(memo, -1, sizeof(memo));	
		int votes = solve(0,M);		
		printf("Case %d: %d\n", ncase++, votes);
		int resto = M;
		para(i,0,N) {
			if (i)
				putchar(' ');
			printf("%d:%d", i, money[i][resto]);			
			resto -= money[i][resto];
		}		
		printf("\n");
		trace("------------\n");
	}
	return 0;
}
