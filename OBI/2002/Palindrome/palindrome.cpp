/**********************************************************
* Palindrome - OBI
*
* Autor: Vinicius J. S. Souza
* Data:04/03/2010
* Tecnicas: programacao dinamica
* Dificuldade(1-10): 8
***********************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>

using namespace std;

#define INF 0x3fffffff
	
int N;
char str[2010];
typedef pair<int,int> pii;
int dp[2010];
bool isPal[2010][2010];

int main() {	
	long s = clock();
	int test = 1;
	while(true) {	
		scanf("%d", &N);
		if (!N) 
			break;
		scanf("%s", str);
		if (test > 1)
			putchar('\n');
		for (int i = 0; i< N; i++)
			for (int k = 0; k < N; k++)
				isPal[i][k] = false;

		for (int i=0; i<N; i++)
		  isPal[i][i] = true;
		for (int j=1; j<N; j++) {
			for (int i=j-1; i>=0; i--) {			
				isPal[i][j] = ((str[i]==str[j]) && (i+1>=j-1 || isPal[i+1][j-1]));		
			}
		}
/*
		for (int i = 0; i <size; i++)
			printf("%d %d\n", isPal[i].first, isPal[i].second);	
*/

	   for (int j=0; j<N; j++) {
		  if (isPal[0][j]) {
			dp[j] = 1;
		  } else {
			int menor = INF;
			for (int i=1; i<=j; i++) {
		  		if (isPal[i][j] && dp[i-1]+1<menor)
				menor = dp[i-1]+1;
		    }
			dp[j] = menor;
		 }
	  }
      printf("Teste %d\n", test++);
	  printf("%d\n\n", dp[N-1]);
	}
//	cout << (double)(clock()-s)/ (double)CLOCKS_PER_SEC << endl;
	return 0;
}
