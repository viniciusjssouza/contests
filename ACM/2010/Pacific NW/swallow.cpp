/****************************************************************
* ACM 2010 - Pacific NorthWest - Zombie Swallow
*
* Autor: Vinicius J. S. Souza
* Data: 19/10/2011
* Tecnicas: Backtrack + Memoization
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<cmath>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false
#define trace(x...) 	if(debug)printf(x);

using namespace std;

long long int S, mini, maxi, N;
long long int sum[150], data[150];
map<long long int, bool> memo[150];

bool solve(long long int nivel, long long int val) {
	if (val >= mini && val <= maxi) {
		return true;
	}
	if (nivel >= N || val > maxi || val + sum[nivel] < mini) {
		return false;
	}
	if (memo[nivel][val])
		return false;
	bool b = solve(nivel+1, val+data[nivel]);
	if (b) return true;
	b = solve(nivel+1, val);
	if (!b) {
		memo[nivel][val] = true;
		return false;
	}
	return true;
}

int main()
{
	scanf("%d" ,&S);
	para(i, 0, S) {
		scanf("%d %d %d", &mini, &maxi, &N);
		para(k, 0, N) {
			scanf("%d", &data[k]);			
			memo[k].clear();	
		}
		sum[N-1] = data[N-1];
		for (int k = N-2; k >= 0; k--) {
			sum[k] = data[k] + sum[k+1];	
		}
		if (solve(0, 0)) {
			printf("Sallow swallow swallows.\n");
		} else {
			printf("Sallow swallow wallows in dust.\n");
		}
	}	
	return 0;
}
